#include "Visual.h"

Visual::Visual()
	:renderer{ Renderer(window) },
	DataRenderer{ Renderer(dataWindow,350,200) }
{
	window.create(VideoMode(ScreenWidth, ScreenHeight), "Fourier Plotter", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);
	window.setPosition(AddVectors(window.getPosition(), Vector2i(0, -25)));

	Image icon;
	icon.loadFromFile("Resources/Textures/Icon.png");
	TransparentGreenScreen(&icon);
	window.setIcon(51, 51, icon.getPixelsPtr());

	std::vector<Complex> points;
	float n = 400;
	for (int i = 0; i < n / 4; i++)
		points.push_back(1 - 4 * i / n + I);
	for (int i = 0; i < n / 4; i++)
		points.push_back(-1 + I * (1 - 4 * i / n));
	for (int i = 0; i < n / 4; i++)
		points.push_back(-1 + 4 * i / n - I);
	for (int i = 0; i < n / 4; i++)
		points.push_back(1 + I * (-1 + 4 * i / n));

	fourier.setPoints(points);

	fourier.fullComputation(settings.error);
	fourier.generatePlot(FunctionSmoothness);

	std::vector<Complex> coef = fourier.getCoef();
	std::vector<int> ordr = fourier.getOrder();

	for (unsigned int i = 0; i < coef.size(); i++)
		printf("coef: %i \tis %s\n", ordr[i],coef[i].str().c_str());
	
	
}

Vector2i Visual::mousePosition()
{
	Vector2i WindowPosition = window.getPosition();
	return Vector2i(Mouse::getPosition().x - WindowPosition.x + Ex, Mouse::getPosition().y - WindowPosition.y - Ey);
}

void Visual::createDataWindow()
{
	dataWindow.create(VideoMode(350, 200), "MiniWindow", Style::Titlebar | Style::Resize);
	dataWindow.setPosition(Vector2i(window.getPosition().x + 820, window.getPosition().y + 430));
}

void Visual::eventsDataWindow()
{
	Event event;
	while (dataWindow.pollEvent(event));

	//DataRenderer.setWindowDim((Vector2i)dataWindow.getSize());
	dataWindow.clear(Color::White);
	DataRenderer.RenderPoint(Complex(0), Color::Black, 10.f);
	dataWindow.display();
}

void Visual::eventCheck()
{
	Vector2i MousePos = mousePosition();

	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::MouseWheelMoved)
			renderer.multiplyScale((float)pow(1.1, event.mouseWheel.delta));

		settings.ErrorBar.EventCheck(event, MousePos);
	}
	if (settings.playing)
		fourier.setTime(fourier.getTime() + 0.001f);

	if (pressing && !Mouse::isButtonPressed(Mouse::Left))
		pressing = false;

	if (settings.DataWindow.EventCheck(MousePos) == Button::Pressed) {
		if (!dataWindow.isOpen())
			createDataWindow();
		else
			dataWindow.close();
	}

	if (dataWindow.isOpen())
		eventsDataWindow();

	else if (settings.playing && !pressing && settings.Pause.EventCheck(MousePos) == Button::Pressed) {
		settings.playing = false;
		pressing = true;
	}
		

	else if (!settings.playing && !pressing && settings.Play.EventCheck(MousePos) == Button::Pressed) {
		settings.playing = true;
		pressing = true;
	}

	else if (Mouse::isButtonPressed(Mouse::Left) && !pressing) {
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
