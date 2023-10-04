#include "Settings.h"

//	Private

void Settings::MovementEvents(int& Change, Vector2f &SidebarPos)
{
	if (IsOpen) {
		if (SetTexture(Sidebar,Textures[OpenedTexture]))
			Change = true;
		if (SidebarPos.x < 0) {
			Sidebar.setPosition(SidebarPos.x + SlideVelocity, SidebarPos.y);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].IncreasePosition(SlideVelocity, 0.f);
			for (unsigned int i = 0; i < Texts.size(); i++)
				Texts[i].setPosition(Texts[i].getPosition().x + SlideVelocity, Texts[i].getPosition().y);
			for (unsigned int i = 0; i < Boxes.size(); i++)
				Boxes[i].increasePosition(SlideVelocity, 0.f);
			selector.IncreasePosition(SlideVelocity, 0.f);
			Change = true;
		}
	}
	else {
		if (SetTexture(Sidebar, Textures[ClosedTexture]))
			Change = true;
		if (SidebarPos.x > -120.f) {
			Sidebar.setPosition(SidebarPos.x - SlideVelocity, SidebarPos.y);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].IncreasePosition(-SlideVelocity, 0.f);
			for (unsigned int i = 0; i < Texts.size(); i++)
				Texts[i].setPosition(Texts[i].getPosition().x - SlideVelocity, Texts[i].getPosition().y);
			for (unsigned int i = 0; i < Boxes.size(); i++)
				Boxes[i].increasePosition(-SlideVelocity, 0.f);
			selector.IncreasePosition(-SlideVelocity, 0.f);
			Change = true;
		}
	}
}

void Settings::MouseEvents(int& Change, Vector2i& MouseScPos, bool& PressingButton)
{
	int tick;
	if (selector.getSize()) {
		tick = Boxes[0].EventCheck(MouseScPos);
		if (tick) {
			Change = tick + 14;
			return;
		}
		tick = Boxes[1].EventCheck(MouseScPos);
		if (tick) {
			Change = tick + 16;
			return;
		}
	}
	tick = Boxes[2].EventCheck(MouseScPos);
	if (tick) {
		Change = tick + 18;
		return;
	}
	

	for (unsigned int i = 0; i < Buttons.size(); i++) {
		
		
		int State = Buttons[i].EventCheck(MouseScPos);
		if (State > 0) {
			Change = 1;
		}
		if (State == Button::Pressed || State == Button::Pressing) {
			if (!buttonCooldown) {
				PressingButton = true;
				buttonCooldown = DefaultButtonCooldown;
				Change = i + 2;
			}
		}
	}
}

//	Public

Settings::Settings() : selector{ Selector(SelectorInitializer, Vector2f(3.f - 120.f, 37.f), true) }
{
	Image image;
	Texture texture;
	image.loadFromFile("Resources/Textures/CustomButtons.png");
	TransparentGreenScreen(&image);
	texture.loadFromImage(image, IntRect(0, 104, 157, 321));
	Textures.push_back(texture);
	texture.loadFromImage(image, IntRect(157, 104, 157, 321));
	Textures.push_back(texture);
	Sidebar.setTexture(Textures[ClosedTexture]);
	Sidebar.setPosition(DefaultSettingsPosition);

	std::string String;
	Text text;
	Font font;
	font.loadFromFile("Resources/Fonts/arial.ttf");
	Fonts.push_back(font);
	text.setFont(Fonts[0]);
	text.setCharacterSize(12);
	text.setFillColor(Color::Black);

	String = "Fourier Depth:\n\nSmoothness:\n\nPoints:\n\n\n\nShow Points:\n\nShow Function\n\nShow Grid:";
	text.setString(String);
	text.setPosition(DefaultSettingsPosition.x + 10.f, DefaultSettingsPosition.y + 65.f);
	Texts.push_back(text);

	String = '0';
	text.setString(String);
	Texts.push_back(text);
	Texts.push_back(text);
	Texts.push_back(text);

	Buttons.push_back(Button(UpButtonInitializer  , Vector2f(112.f - 120.f,  67.f), true));
	Buttons.push_back(Button(DownButtonInitializer, Vector2f(112.f - 120.f,  79.f), true));
	Buttons.push_back(Button(UpButtonInitializer  , Vector2f(112.f - 120.f,  95.f), true));
	Buttons.push_back(Button(DownButtonInitializer, Vector2f(112.f - 120.f, 107.f), true));
	Buttons.push_back(Button(UpButtonInitializer  , Vector2f(112.f - 120.f, 123.f), true));
	Buttons.push_back(Button(DownButtonInitializer, Vector2f(112.f - 120.f, 135.f), true));
	Buttons.push_back(Button(BigButtonInitializer , Vector2f(  7.f - 120.f, 150.f), true, "Duplicate", Vector2f( 9.f, 4.f), font, 12));
	Buttons.push_back(Button(BigButtonInitializer , Vector2f( 83.f - 120.f, 150.f), true, "Draw"     , Vector2f(18.f, 4.f), font, 12));
	Buttons.push_back(Button(BigButtonInitializer , Vector2f(  7.f - 120.f, 264.f), true, "New"      , Vector2f(21.f, 4.f), font, 12));
	Buttons.push_back(Button(RedButtonInitializer , Vector2f( 83.f - 120.f, 264.f), true, "Delete"   , Vector2f(17.f, 4.f), font, 12));
	Buttons.push_back(Button(BlueButtonInitializer, Vector2f(  7.f - 120.f, 292.f), true, "Load"     , Vector2f(21.f, 4.f), font, 12));
	Buttons.push_back(Button(BlueButtonInitializer, Vector2f( 83.f - 120.f, 292.f), true, "Save"     , Vector2f(20.f, 4.f), font, 12));
	Buttons.push_back(Button(ColorButtonInitializer, Vector2f( 130.f - 120.f, 38.f), true));
	
	Boxes.push_back(TickBox("Resources/Textures/CustomButtons.png", Vector2i(363, 430), Vector2i(388, 430), Vector2i(16, 16), Vector2f(10, 182), true, true));
	Boxes.push_back(TickBox("Resources/Textures/CustomButtons.png", Vector2i(363, 430), Vector2i(388, 430), Vector2i(16, 16), Vector2f(10, 210), true, true));
	Boxes.push_back(TickBox("Resources/Textures/CustomButtons.png", Vector2i(363, 430), Vector2i(388, 430), Vector2i(16, 16), Vector2f(10, 238), true, true));

	selector.pushBack("Untitled 1");

	IsOpen = false;

}

void Settings::setValues(std::vector<int> &values)
{
	Values = values;
	int x, n = Values[FourierDepth];
	std::string String = std::to_string(n);
	if (n)
		x = (int)(log(n * 1.0001) / log(10));
	else
		x = 0;
	Texts[1].setString(String);
	Texts[1].setPosition(Sidebar.getPosition().x + 100.f - 7.f * x, Sidebar.getPosition().y + 65.f);
	n = Values[PointsFunction];
	String = std::to_string(n);
	if (n)
		x = (int)(log(n * 1.0001) / log(10));
	else
		x = 0;
	Texts[2].setString(String);
	Texts[2].setPosition(Sidebar.getPosition().x + 100.f - 7.f * x, Sidebar.getPosition().y + 94.f);
	n = Values[FourierPoints];
	String = std::to_string(n);
	if (n)
		x = (int)(log(n * 1.0001) / log(10));
	else
		x = 0;
	Texts[3].setString(String);
	Texts[3].setPosition(Sidebar.getPosition().x + 100.f - 7.f * x, Sidebar.getPosition().y + 123.f);

	
}

void Settings::setPointsVisibility(bool T)
{
	Boxes[0].setState(T);
}

void Settings::setFunctionVisibility(bool T)
{
	Boxes[1].setState(T);
}

void Settings::close()
{
	IsOpen = false;
}

void Settings::open()
{
	IsOpen = true;
}

int Settings::EventCheck(Vector2i MouseScPos, bool Occupied, bool& PressingButton)
{
	if (Freeze && Mouse::isButtonPressed(Mouse::Left))
		return 0;
	else
		Freeze = false;
	int Change = false;
	Vector2f SidebarPos = Sidebar.getPosition();
	MovementEvents(Change, SidebarPos);
	int SelectorChange = selector.EventCheck(MouseScPos);
	if (SelectorChange >= -1) {
		if (SelectorChange > -1)
			Freeze = true;
		for (int i = 0; i < (int)Buttons.size(); i++)
			Buttons[i].setTexture(0);
		return SelectorChange + 30;
	}
	if (!Occupied && IsOpen)
		MouseEvents(Change, MouseScPos, PressingButton);

	if (Mouse::isButtonPressed(Mouse::Left) && !Occupied) {
		if (buttonCooldown)
			buttonCooldown--;
		if (InsideRectangle(MouseScPos, IncreaseVector((Vector2f)Sidebar.getPosition(),120.f,0.f),Vector2i(37,28)) && !buttonCooldown) {
			buttonCooldown = DefaultButtonCooldown;
			PressingButton = true;
			Change = 1;
			if (IsOpen)
				IsOpen = false;
			else
				IsOpen = true;
		}
	}
	else {
		buttonCooldown = 0;
		PressingButton = false;
	}
	return Change;
}

void Settings::Render(Renderer& renderer)
{
	renderer.RenderSprite(Sidebar);
	if (IsOpen) {
		for (int i = 0; i < (int)Buttons.size(); i++)
			Buttons[i].Render(renderer);
		renderer.RenderTexts(Texts);
		selector.Render(renderer);
		for (int i = 0; i < (int)Boxes.size(); i++)
			Boxes[i].Render(renderer);
	}
	return;
}