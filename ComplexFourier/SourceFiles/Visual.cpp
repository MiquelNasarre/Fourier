#include "Visual.h"

Visual::Visual(std::string filename)
	:renderer{ Renderer(window) },
	DataRenderer{ Renderer(dataWindow,350,200) }
{
	if (filename.size())
		loadFile(filename);

	else {
		std::vector<Complex> points;
		float n = 200;
		for (int i = 0; i < n / 4; i++)
			points.push_back(1 - 4 * i / n + I);
		for (int i = 0; i < n / 4; i++)
			points.push_back(-1 + I * (1 - 4 * i / n));
		for (int i = 0; i < n / 4; i++)
			points.push_back(-1 + 4 * i / n - I);
		for (int i = 0; i < n / 4; i++)
			points.push_back(1 + I * (-1 + 4 * i / n));

		fourier.setPoints(points);
		computeFourier();
	}

	window.create(VideoMode(ScreenWidth, ScreenHeight), "Fourier Plotter", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);
	window.setPosition(window.getPosition() + Vector2i(0, -25));

	Image icon;
	icon.loadFromFile("Resources/Textures/Icon.png");
	TransparentGreenScreen(&icon);
	window.setIcon(51, 51, icon.getPixelsPtr());
	
}

Vector2i Visual::mousePosition()
{
	Vector2i WindowPosition = window.getPosition();
	return Vector2i(Mouse::getPosition().x - WindowPosition.x + Ex, Mouse::getPosition().y - WindowPosition.y - Ey);
}

void Visual::createDataWindow()
{
	dataWindow.create(VideoMode((unsigned int)dataWindowWidth, (unsigned int)dataWindowHeight), "", Style::Resize);
	dataWindow.setPosition(Vector2i(window.getPosition() + (Vector2i)window.getSize() + Vector2i(-dataWindowWidth - 20, -dataWindowHeight - 20)));

	view = View(sf::FloatRect(0, 0, dataWindowWidth, dataWindowHeight));

	dataWindow.setView(view);
	
}

void Visual::eventsDataWindow()
{
	dataWindow.requestFocus();
	Event event;
	while (dataWindow.pollEvent(event)) {
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			dataWindow.close();
		if (event.type == sf::Event::Resized) {
			view.setSize((float)event.size.width, (float)event.size.height);
			view.setCenter(float(event.size.width / 2), float(event.size.height / 2));
			dataWindow.setView(view);
		}
	}

	std::vector<Complex> coef = fourier.getCoef();
	std::vector<int> order = fourier.getOrder();

	float width = (float)dataWindow.getSize().x;
	float height = (float)dataWindow.getSize().y;

	RectangleShape rect(Vector2f(2*(width - 2 * HorizontalMargin) / coef.size() - 1, 1.f));
	rect.setFillColor(DataColor);

	Font font;
	font.loadFromFile(ArialFontFile);
	Text num;
	num.setFont(font);
	num.setFillColor(DataColor);
	num.setCharacterSize(9);

	float bigger = 0, x;
	std::vector<float> absCoef;
	for (unsigned int i = 0; i < coef.size(); i++) {
		x = coef[i].abs();
		absCoef.push_back(x);
		if (x > bigger)
			bigger = x;
	}

	int minimum = order[0];
	for (unsigned int i = 0; i < order.size(); i++) {
		if (order[i] > 0 && minimum > order[i])
			minimum = order[i];
	}

	int modulus = 1;
	if (order.size() > 40)
		modulus = 2;
	if (order.size() > 100)
		modulus = 5;
	if (order.size() > 200)
		modulus = 10;
	if (order.size() > 500)
		modulus = 20;

	dataWindow.clear(BackgroundColor);

	for (unsigned int i = 0; i < coef.size(); i++) {
		rect.setScale(1.f, -absCoef[i] / bigger * (height - 2 * VerticalMargin) / 2 - 1);
		rect.setPosition(HorizontalMargin + (order[i] * (float)pow(-1, i) - minimum) * (width - 2 * HorizontalMargin) / order.size() * 2, height - VerticalMargin - height * (i % 2) / 2);
		dataWindow.draw(rect);
		
		if (!(order[i] % modulus)) {
			num.setString(std::to_string(order[i] * (int)pow(-1, i)));
			num.setPosition(rect.getPosition() + rect.getSize() / 2 - num.getGlobalBounds().getSize() / 2 + Vector2f(0.f, 4.f));
			dataWindow.draw(num);
		}
	}

	Vertex line0[] = { Vertex(Vector2f(HorizontalMargin / 2,height - VerticalMargin / 2),DataColor),Vertex(Vector2f(width - HorizontalMargin / 2,height - VerticalMargin / 2),DataColor) };
	dataWindow.draw(line0, 2, Lines);
	Vertex line1[] = { Vertex(Vector2f(HorizontalMargin / 2,height / 2 - VerticalMargin / 2),DataColor),Vertex(Vector2f(width - HorizontalMargin / 2,height / 2 - VerticalMargin / 2),DataColor) };
	dataWindow.draw(line1, 2, Lines);
	Vertex line2[] = { Vertex(Vector2f(HorizontalMargin - VerticalMargin / 2,height - VerticalMargin / 2),DataColor),Vertex(Vector2f(HorizontalMargin - VerticalMargin / 2,height / 2),DataColor) };
	dataWindow.draw(line2, 2, Lines);
	Vertex line3[] = { Vertex(Vector2f(HorizontalMargin - VerticalMargin / 2,height / 2 - VerticalMargin / 2),DataColor),Vertex(Vector2f(HorizontalMargin - VerticalMargin / 2, 0.f), DataColor) };
	dataWindow.draw(line3, 2, Lines);

	num.setString("NEGATIVE");
	num.setPosition(width - num.getGlobalBounds().width - HorizontalMargin, 20.f);
	dataWindow.draw(num);

	num.setString("POSITIVE");
	num.setPosition(width - num.getGlobalBounds().width - HorizontalMargin, height / 2 + 20.f);
	dataWindow.draw(num);

	dataWindow.display();
}

void Visual::drawingEvents()
{
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::MouseWheelMoved)
			renderer.multiplyScale((float)pow(1.1, event.mouseWheel.delta));
	}

	Complex MouseComplex = renderer.ComplexPos((Vector2f)mousePosition());

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		drawing = false;
		if (canva.size() > 1) {
			std::vector<Complex> plot;
			for (int i = 0; i < settings.points; i++) {
				float s = float(i * canva.size()) / settings.points;
				float ds = s - int(s);
				plot.push_back(canva[(int)s] * (1 - ds) + canva[int(s + 1) % canva.size()] * ds);
			}
			renderer.setCenter(renderer.getCenter() + fourier.setPoints(plot));
			computeFourier();
			fourier.setTime(0.f);
			demo = true;
			settings.playing = true;
		}
		canva.clear();
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		drawing = false;
		canva.clear();
		return;
	}
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (pressing)
			return;
		if (!canva.size())
			return canva.push_back(MouseComplex);
		if ((canva[canva.size() - 1] - MouseComplex).abs() > 1.f / renderer.getScale())
			return canva.push_back(MouseComplex);
	}
	else
		pressing = false;
}

void Visual::computeFourier()
{
	fourier.fullComputation(settings.error);
	fourier.generatePlot(FunctionSmoothness);

	std::vector<Complex> coef = fourier.getCoef();
	std::vector<int> ordr = fourier.getOrder();
	printf("\n\n");
	for (unsigned int i = 0; i < coef.size(); i++)
		printf("coef: %i \tis %s\n", ordr[i], coef[i].str().c_str());

	std::string ComputedError = std::to_string(fourier.discreteError());
	ComputedError.pop_back();
	ComputedError.pop_back();
	settings.texts[Settings::DiscreteErrorText].setString(ComputedError);
	settings.texts[Settings::DiscreteErrorText].setPosition(Vector2f(142.f - settings.texts[Settings::DiscreteErrorText].getLocalBounds().width, 115.f));
	settings.texts[Settings::CoefficientsText].setString(std::to_string(coef.size()));
	settings.texts[Settings::CoefficientsText].setPosition(Vector2f(142.f - settings.texts[Settings::CoefficientsText].getLocalBounds().width, 140.f));
}

void Visual::saveFile(std::string filename)
{
	if (!filename.size())
		filename = Popup::InputString();
	if (!filename.size())
		return;
	std::string location = "SaveFiles/" + filename + ".dat";
	FILE* file = fopen(location.c_str(), "w");
	std::vector<Complex> points = fourier.getPoints();
	for (unsigned int i = 0; i < points.size(); i++)
		fprintf(file, "%f %f\n", points[i].a, points[i].b);
	fclose(file);
}

void Visual::loadFile(std::string filename)
{
	if (!filename.size())
		filename = Popup::InputString("Name of the file");
	if (!filename.size())
		return;
	std::string location = "SaveFiles/" + filename + ".dat";
	FILE* file = fopen(location.c_str(), "r");
	std::vector<Complex> points;
	float a, b;
	while (fscanf(file, "%f %f\n", &a, &b) != EOF)
		points.push_back(a + b * I);
	fclose(file);
	fourier.setPoints(points);
	computeFourier();
	demo = true;
	fourier.setTime(0);
	settings.points = points.size();
	settings.NumberPoints.setNumber((float)settings.points);
	settings.playing = true;
}

void Visual::eventCheck()
{
	if (drawing)
		return drawingEvents();
	Vector2i MousePos = mousePosition();

	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::MouseWheelMoved)
			renderer.multiplyScale((float)pow(1.1, event.mouseWheel.delta));

		if (settings.ErrorBar.EventCheck(event, MousePos)) {
			settings.error = settings.ErrorBar.getNumber();
			computeFourier();
		}

		if (settings.NumberPoints.EventCheck(event, MousePos)) {
			settings.points = (int)settings.NumberPoints.getNumber();
			if (settings.points < 2) {
				settings.points = 2;
				settings.NumberPoints.setNumber((float)settings.points);
			}
			fourier.setPoints(settings.points);
			computeFourier();
		}
	}
	if (settings.playing) {
		if (demo && fourier.getTime() + speed > 1) {
			fourier.setTime(1.f);
			settings.playing = false;
			demo = false;
		}
		else
			fourier.setTime(fourier.getTime() + speed);
	}
		

	if (pressing && !Mouse::isButtonPressed(Mouse::Left))
		pressing = false;

	if (dataWindow.isOpen())
		eventsDataWindow();

	if (settings.DataWindow.eventCheck(MousePos) == Button::Pressed) {
		if (!dataWindow.isOpen())
			createDataWindow();
		else
			dataWindow.close();
		MouseTracker = MousePos;
		PrevCenter = renderer.getCenter();
		pressing = true;
		return;
	}

	else if (settings.playing && !pressing && settings.Pause.eventCheck(MousePos) == Button::Pressed) {
		settings.playing = false;
		MouseTracker = MousePos;
		PrevCenter = renderer.getCenter();
		pressing = true;
		return;
	}
	
	else if (!settings.playing && !pressing && settings.Play.eventCheck(MousePos) == Button::Pressed) {
		settings.playing = true;
		MouseTracker = MousePos;
		PrevCenter = renderer.getCenter();
		pressing = true;
		return;
	}

	else if (settings.pointsVisible && !pressing && settings.Hide.eventCheck(MousePos) == Button::Pressed) {
		settings.pointsVisible = false;
		MouseTracker = MousePos;
		PrevCenter = renderer.getCenter();
		pressing = true;
		return;
	}

	else if (!settings.pointsVisible && !pressing && settings.Show.eventCheck(MousePos) == Button::Pressed) {
		settings.pointsVisible = true;
		MouseTracker = MousePos;
		PrevCenter = renderer.getCenter();
		pressing = true;
		return;
	}

	else if (!pressing && settings.IncreaseSpeed.eventCheck(MousePos) == Button::Pressed) {
		speed *= speedMult;
		MouseTracker = MousePos;
		PrevCenter = renderer.getCenter();
		pressing = true;
		return;
	}

	else if (!pressing && settings.DecreaseSpeed.eventCheck(MousePos) == Button::Pressed) {
		speed /= speedMult;
		MouseTracker = MousePos;
		PrevCenter = renderer.getCenter();
		pressing = true;
		return;
	}

	else if (!pressing && settings.Draw.eventCheck(MousePos) == Button::Pressed) {
		drawing = true;
		pressing = true;
		CircleView = 0;
		dataWindow.close();
		return;
	}

	else if (!pressing && settings.Save.eventCheck(MousePos) == Button::Pressed)
		return saveFile();

	else if (!pressing && settings.Load.eventCheck(MousePos) == Button::Pressed)
		return loadFile();

	else if (Mouse::isButtonPressed(Mouse::Left) && !pressing && window.hasFocus()) {
		for (int i = (int)fourier.getCoef().size() - 1; i > 0; i--) {
			if (InsideCircle(MousePos, renderer.ScPos(fourier.getCircleCenter(i)), int(fourier.getCircleRadius(i) * renderer.getScale()))) {
				CircleView = i;
				pressing = true;
				break;
			}
		}
	}

	if (Mouse::isButtonPressed(Mouse::Left) && !pressing){
		CircleView = 0;
		MouseTracker = MousePos;
		PrevCenter = renderer.getCenter();
	}

	if (pressing && !CircleView)
		renderer.setCenter((MouseTracker.x - MousePos.x + I * (MousePos.y - MouseTracker.y)) / renderer.getScale() + PrevCenter);

	if (CircleView)
		renderer.setCenter(fourier.getCircleCenter(CircleView));

	if (Mouse::isButtonPressed(Mouse::Left))
		pressing = true;
}

void Visual::render()
{
	window.clear(BackgroundColor);
	if (Plain) {
		renderer.RenderGrid();
		renderer.RenderAxis();
	}
	if (drawing) {
		if (!Mouse::isButtonPressed(Mouse::Left) && canva.size())
			renderer.RenderPoint(canva[canva.size() - 1], Color(50, 50, 50, 255), 2.f);
		renderer.RenderPlot(canva,PointsColor);
		window.display();
		return;
	}
	if (settings.pointsVisible)
		fourier.renderPoints(renderer);
	fourier.renderPartialPlot(renderer);
	fourier.renderCircles(renderer, renderer.getScale() / 200);
	settings.render(window);
	window.display();
}

void Visual::mainLoop()
{
	while (window.isOpen()) {
		eventCheck();
		render();
	}
}
