#include "Settings.h"

//	Private

void Settings::MovementEvents(int& Change, Vector2f &SidebarPos)
{
	if (IsOpen) {
		if (Sidebar.getTexture() == &Textures[ClosedTexture]) {
			Sidebar.setTexture(Textures[OpenedTexture]);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].setVisibility(true);
			selector.SetVisibility(true);
			for (unsigned int i = 0; i < Boxes.size(); i++)
				Boxes[i].setVisibility(true);
			Change = true;
		}
		if (SidebarPos.x < 0) {
			Sidebar.setPosition(SidebarPos.x + SlideVelocity, SidebarPos.y);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].IncreasePosition(SlideVelocity, 0.f);
			for (unsigned int i = 0; i < Texts.size(); i++)
				Texts[i].setPosition(Texts[i].getPosition().x + SlideVelocity, Texts[i].getPosition().y);
			selector.IncreasePosition(SlideVelocity, 0.f);
			for (unsigned int i = 0; i < Boxes.size(); i++)
				Boxes[i].increasePosition(SlideVelocity, 0.f);
			Change = true;
		}
	}
	else {
		if (Sidebar.getTexture() == &Textures[OpenedTexture]) {
			Sidebar.setTexture(Textures[ClosedTexture]);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].setVisibility(false);
			selector.SetVisibility(false);
			Change = true;
		}
		if (SidebarPos.x > -120.f) {
			Sidebar.setPosition(SidebarPos.x - SlideVelocity, SidebarPos.y);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].IncreasePosition(-SlideVelocity, 0.f);
			for (unsigned int i = 0; i < Texts.size(); i++)
				Texts[i].setPosition(Texts[i].getPosition().x - SlideVelocity, Texts[i].getPosition().y);
			selector.IncreasePosition(-SlideVelocity, 0.f);
			for (unsigned int i = 0; i < Boxes.size(); i++)
				Boxes[i].increasePosition(-SlideVelocity, 0.f);
			Change = true;
		}
	}
}

void Settings::MouseEvents(int& Change, Vector2i& MouseScPos, bool& PressingButton)
{
	int tick = Boxes[0].EventCheck(MouseScPos);
	if (tick) {
		Change = tick + 14;
		return;
	}
	tick = Boxes[1].EventCheck(MouseScPos);
	if (tick) {
		Change = tick + 16;
		return;
	}
	for (unsigned int i = 0; i < Buttons.size(); i++) {
		
		
		int State = Buttons[i].ButtonEvents(MouseScPos);
		if (State > 0) {
			Change = 1;
		}
		if (State == 3 || State == -3) {
			if (!buttonCooldown) {
				PressingButton = true;
				buttonCooldown = DefaultButtonCooldown;
				Change = i + 2;
			}
		}
	}
}

//	Public

Settings::Settings() : selector{ Selector(SelectorInitializer, Vector2f(3.f - 120.f, 37.f), true) } {
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

	String = "Fourier Depth:\n\nSmoothness:\n\nPoints:\n\n     Reset\t\t\t   Draw\n\nShow Points:\n\nShow Function\n\n\n\n      New\t\t\t    Delete\n\n      Load\t\t\t    Save";
	text.setString(String);
	text.setPosition(DefaultSettingsPosition.x + 10.f, DefaultSettingsPosition.y + 35.f + MoveDown);
	Texts.push_back(text);

	String = '0';
	text.setString(String);
	Texts.push_back(text);
	Texts.push_back(text);
	Texts.push_back(text);

	Buttons.push_back(Button(UpButtonInitializer  , Vector2f(112.f - 120.f,  37.f + MoveDown), false));
	Buttons.push_back(Button(DownButtonInitializer, Vector2f(112.f - 120.f,  49.f + MoveDown), false));
	Buttons.push_back(Button(UpButtonInitializer  , Vector2f(112.f - 120.f,  65.f + MoveDown), false));
	Buttons.push_back(Button(DownButtonInitializer, Vector2f(112.f - 120.f,  77.f + MoveDown), false));
	Buttons.push_back(Button(UpButtonInitializer  , Vector2f(112.f - 120.f,  93.f + MoveDown), false));
	Buttons.push_back(Button(DownButtonInitializer, Vector2f(112.f - 120.f, 105.f + MoveDown), false));
	Buttons.push_back(Button(BigButtonInitializer , Vector2f(  7.f - 120.f, 120.f + MoveDown), false));
	Buttons.push_back(Button(BigButtonInitializer , Vector2f( 83.f - 120.f, 120.f + MoveDown), false));
	Buttons.push_back(Button(BigButtonInitializer , Vector2f(  7.f - 120.f, 232.f + MoveDown), false));
	Buttons.push_back(Button(RedButtonInitializer , Vector2f( 83.f - 120.f, 232.f + MoveDown), false));
	Buttons.push_back(Button(BlueButtonInitializer, Vector2f(  7.f - 120.f, 260.f + MoveDown), false));
	Buttons.push_back(Button(BlueButtonInitializer, Vector2f( 83.f - 120.f, 260.f + MoveDown), false));
	Buttons.push_back(Button(ColorButtonInitializer, Vector2f( 130.f - 120.f, 38.f), false));
	
	Boxes.push_back(TickBox("Resources/Textures/CustomButtons.png", Vector2i(363, 430), Vector2i(388, 430), Vector2i(16, 16), Vector2f(10, 182), true, true));
	Boxes.push_back(TickBox("Resources/Textures/CustomButtons.png", Vector2i(363, 430), Vector2i(388, 430), Vector2i(16, 16), Vector2f(10, 210), true, true));

	selector.AddOption("Untitled 1");

	IsOpen = false;

}

bool Settings::SettingsIcon(Vector2i& MouseScPos)
{
	if (MouseScPos.x >= Sidebar.getPosition().x + 120.f &&
		MouseScPos.y >= Sidebar.getPosition().y &&
		MouseScPos.x < Sidebar.getPosition().x + 157.f &&
		MouseScPos.y < Sidebar.getPosition().y + 28.f)
		return true;
	return false;
}

void Settings::SetValues(std::vector<int> values)
{
	Values = values;
	int x, n = Values[FourierDepth];
	std::string String = std::to_string(n);
	if (n)
		x = (int)(log(n * 1.0001) / log(10));
	else
		x = 0;
	Texts[1].setString(String);
	Texts[1].setPosition(Sidebar.getPosition().x + 100.f - 7.f * x, Sidebar.getPosition().y + 35.f + MoveDown);
	n = Values[PointsFunction];
	String = std::to_string(n);
	if (n)
		x = (int)(log(n * 1.0001) / log(10));
	else
		x = 0;
	Texts[2].setString(String);
	Texts[2].setPosition(Sidebar.getPosition().x + 100.f - 7.f * x, Sidebar.getPosition().y + 64.f + MoveDown);
	n = Values[FourierPoints];
	String = std::to_string(n);
	if (n)
		x = (int)(log(n * 1.0001) / log(10));
	else
		x = 0;
	Texts[3].setString(String);
	Texts[3].setPosition(Sidebar.getPosition().x + 100.f - 7.f * x, Sidebar.getPosition().y + 93.f + MoveDown);

	
}

void Settings::DrawSettings(Renderer& renderer)
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

int Settings::SettingsEvents(Vector2i MouseScPos, bool Occupied, bool& PressingButton)
{
	int Change = false;
	Vector2f SidebarPos = Sidebar.getPosition();
	MovementEvents(Change, SidebarPos);
	int SelectorChange = selector.SelectorEvents(MouseScPos);
	if (SelectorChange >= -1)return SelectorChange + 30;
	if (!Occupied && IsOpen)
		MouseEvents(Change, MouseScPos, PressingButton);

	if (Mouse::isButtonPressed(Mouse::Left) && !Occupied) {
		if (buttonCooldown)
			buttonCooldown--;
		if (SettingsIcon(MouseScPos) && !buttonCooldown) {
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

void Settings::DeleteSelected()
{
	selector.RemoveOption();
}

void Settings::EmptySelector()
{
	selector.RemoveAll();
}

void Settings::setSelector(int n)
{
	selector.SetCurrentSelected(n);
}

std::string Settings::getSelectorString(int N)
{
	return selector.getString(N);
}

void Settings::AddToSelector(std::string String)
{
	selector.AddOption(String);
}

void Settings::setPointsVisibility(bool T)
{
	Boxes[0].setState(T);
}

void Settings::setFunctionVisibility(bool T)
{
	Boxes[1].setState(T);
}
