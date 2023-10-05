#include "ToolBox.h"

ToolBox::ToolBox()
	:IconButton{ Button(ToolsButtonInitializer,DefaultToolBoxPos) }
{
	Image image;
	image.loadFromFile(TexturesFile);
	TransparentGreenScreen(&image);
	TexBox.loadFromImage(image, IntRect(658, 326, 329, 106));
	Box.setTexture(TexBox);
	Box.setPosition(AddVectors(Position, Vector2f(50.f, -70.f)));

	Tools.push_back(Button(UpperButtonInitializer , AddVectors(Position, Vector2f( 90.f,-56.f))));
	Tools.push_back(Button(DownerButtonInitializer, AddVectors(Position, Vector2f( 90.f,  2.f))));
	Tools.push_back(Button(LeftButtonInitializer  , AddVectors(Position, Vector2f( 63.f,-29.f))));
	Tools.push_back(Button(RightButtonInitializer , AddVectors(Position, Vector2f(121.f,-29.f))));
	Tools.push_back(Button(CenterButtonInitializer, AddVectors(Position, Vector2f( 90.f,-29.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(741,113),Vector2i(741,145),Vector2i(741,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(165.f, -50.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(774,113),Vector2i(774,145),Vector2i(774,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(165.f, -10.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(807,113),Vector2i(807,145),Vector2i(807,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(205.f, -50.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(840,113),Vector2i(840,145),Vector2i(840,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(205.f, -10.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(873,113),Vector2i(873,145),Vector2i(873,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(245.f, -50.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(906,113),Vector2i(906,145),Vector2i(906,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(245.f, -10.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(939,113),Vector2i(939,145),Vector2i(939,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(285.f, -50.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(972,113),Vector2i(972,145),Vector2i(972,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(285.f, -10.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(1005,113),Vector2i(1005,145),Vector2i(1005,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(325.f, -50.f))));
	Tools.push_back(Button(TexturesFile, std::vector{ Vector2i(1038,113),Vector2i(1038,145),Vector2i(1038,177) }, Vector2i(30, 30), Vector2f(1.f, 1.f), AddVectors(Position, Vector2f(325.f, -10.f))));
}

Vector2f ToolBox::centerFourier(Fourier& fourier)
{
	int n = fourier.GetNumberPoints();
	float x = 0.f, y = 0.f;
	Vector2f P;
	for (int i = 0; i < n; i++) {
		P = fourier.getPosition(i);
		x += P.x;
		y += P.y;
	}
	return Vector2f(x / n, y / n);
}

void ToolBox::moveFourier(Fourier& fourier, Vector2f dV)
{
	std::vector<Point>& Points = *fourier.GetPoints();
	for (int i = 0; i < (int)Points.size(); i++) {
		Points[i].Position.x += dV.x;
		Points[i].Position.y += dV.y;
	}
}

void ToolBox::moveToCenter(Fourier& fourier)
{
	Vector2f center = centerFourier(fourier);
	Vector2f dV = Vector2f(-center.x, -center.y);
	moveFourier(fourier, dV);
}

void ToolBox::ExpandFourier(Fourier& fourier, float k)
{
	Vector2f center = centerFourier(fourier);
	moveToCenter(fourier);
	std::vector<Point>& Points = *fourier.GetPoints();
	for (int i = 0; i < (int)Points.size(); i++) {
		Points[i].Position.x *= k;
		Points[i].Position.y *= k;
	}
	moveFourier(fourier, center);
}

void ToolBox::RotateFourier(Fourier& fourier, double theta)
{
	Vector2f center = centerFourier(fourier);
	moveToCenter(fourier);
	float x, y;
	std::vector<Point>& Points = *fourier.GetPoints();
	for (int i = 0; i < (int)Points.size(); i++) {
		x = Points[i].Position.x;
		y = Points[i].Position.y;
		Points[i].Position.x = float(x * cos(theta) - y * sin(theta));
		Points[i].Position.y = float(y * cos(theta) + x * sin(theta));
	}
	moveFourier(fourier, center);
}

void ToolBox::ExpHortFourier(Fourier& fourier, float k)
{
	Vector2f center = centerFourier(fourier);
	moveToCenter(fourier);
	std::vector<Point>& Points = *fourier.GetPoints();
	for (int i = 0; i < (int)Points.size(); i++)
		Points[i].Position.x *= k;
	moveFourier(fourier, center);
}

void ToolBox::ExpVertFourier(Fourier& fourier, float k)
{
	Vector2f center = centerFourier(fourier);
	moveToCenter(fourier);
	std::vector<Point>& Points = *fourier.GetPoints();
	for (int i = 0; i < (int)Points.size(); i++)
		Points[i].Position.y *= k;
	moveFourier(fourier, center);
}

bool ToolBox::EventCheck(Vector2i MousePos, Fourier& fourier)
{
	bool change = false;

	if (isOpen && Position.y > DefaultToolBoxPos.y) {
		change = true;
		Position.y -= 5;
		Box.setPosition(AddVectors(Position, Vector2f(50.f, -70.f)));
		for (int i = 0; i < (int)Tools.size(); i++)
			Tools[i].IncreasePosition(0.f, -5.f);
	}
	if (!isOpen && Position.y < DefaultToolBoxPos.y + 110.f) {
		change = true;
		Position.y += 5;
		Box.setPosition(AddVectors(Position, Vector2f(50.f, -70.f)));
		for (int i = 0; i < (int)Tools.size(); i++)
			Tools[i].IncreasePosition(0.f, 5.f);
	}

	int event = IconButton.EventCheck(MousePos);
	if (event > 0) {
		change = true;
		if (event == Button::Pressed) {
			if (isOpen)
				isOpen = false;
			else
				isOpen = true;
		}
	}
	if (isOpen) {
		event = Tools[MoveUp].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			moveFourier(fourier, Vector2f(0.f, MovementSpeed));

		event = Tools[MoveDown].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			moveFourier(fourier, Vector2f(0.f, -MovementSpeed));

		event = Tools[MoveLeft].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			moveFourier(fourier, Vector2f(-MovementSpeed, 0.f));

		event = Tools[MoveRight].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			moveFourier(fourier, Vector2f(MovementSpeed, 0.f));

		event = Tools[Center].EventCheck(MousePos);
		if (event > 0)
			change = true;
		if (event == Button::Pressed)
			moveToCenter(fourier);

		event = Tools[RotateRight].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			RotateFourier(fourier, -RotatingRate);

		event = Tools[RotateLeft].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			RotateFourier(fourier, RotatingRate);

		event = Tools[FlipHorizontal].EventCheck(MousePos);
		if (event > 0)
			change = true;
		if (event == Button::Pressed)
			ExpHortFourier(fourier, -1);

		event = Tools[FlipVertical].EventCheck(MousePos);
		if (event > 0)
			change = true;
		if (event == Button::Pressed)
			ExpVertFourier(fourier, -1);

		event = Tools[Expand].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			ExpandFourier(fourier, ExpansionRate);

		event = Tools[Shrink].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			ExpandFourier(fourier, ShrinkingRate);

		event = Tools[SquishHort].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			ExpHortFourier(fourier, ShrinkingRate);

		event = Tools[SquishVert].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			ExpVertFourier(fourier, ShrinkingRate);

		event = Tools[EnlargeHort].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			ExpHortFourier(fourier, ExpansionRate);

		event = Tools[EnlargeVert].EventCheck(MousePos);
		if (event > 0 || event == Button::Pressing)
			change = true;
		if (event == Button::Pressed || event == Button::Pressing)
			ExpVertFourier(fourier, ExpansionRate);
	}


	return change;
}

void ToolBox::Render(Renderer& renderer)
{
	IconButton.Render(renderer);
	renderer.RenderSprite(Box);
	for (int i = 0; i < (int)Tools.size(); i++)
		Tools[i].Render(renderer);
}
