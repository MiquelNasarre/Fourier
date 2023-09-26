#include "Settings.h"

//	Private

void Settings::MovementEvents(int& Change, Vector2f &SidebarPos)
{
	if (IsOpen) {
		if (Sidebar.getTexture() == &Textures[ClosedTexture]) {
			Sidebar.setTexture(Textures[OpenedTexture]);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].ToBe = true;
			Change = true;
		}
		if (SidebarPos.x < 0) {
			Sidebar.setPosition(SidebarPos.x + SlideVelocity, SidebarPos.y);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].IncreasePosition(SlideVelocity, 0.f);
			for (unsigned int i = 0; i < Texts.size(); i++)
				Texts[i].setPosition(Texts[i].getPosition().x + SlideVelocity, Texts[i].getPosition().y);
			Change = true;
		}
	}
	else {
		if (Sidebar.getTexture() == &Textures[OpenedTexture]) {
			Sidebar.setTexture(Textures[ClosedTexture]);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].ToBe = false;
			Change = true;
		}
		if (SidebarPos.x > -120.f) {
			Sidebar.setPosition(SidebarPos.x - SlideVelocity, SidebarPos.y);
			for (unsigned int i = 0; i < Buttons.size(); i++)
				Buttons[i].IncreasePosition(-SlideVelocity, 0.f);
			for (unsigned int i = 0; i < Texts.size(); i++)
				Texts[i].setPosition(Texts[i].getPosition().x - SlideVelocity, Texts[i].getPosition().y);
			Change = true;
		}
	}
}

void Settings::MouseEvents(int& Change, Vector2i& MouseScPos, bool& PressingButton)
{
	for (unsigned int i = 0; i < Buttons.size(); i++) {
		if (Buttons[i].IsinPos(MouseScPos)) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (Buttons[i].State != 2) {
					Buttons[i].State = 2;
				}
				if (!buttonCooldown) {
					PressingButton = true;
					buttonCooldown = DefaultButtonCooldown;
					Change = i + 2;
				}
			}
			else if (Buttons[i].State != 1) {
				Buttons[i].State = 1;
				Change = true;
			}
		}
		else if (Buttons[i].State != 0) {
			Buttons[i].State = 0;
			Change = true;
		}
	}
}

//	Public

Settings::Settings() {
	Image image;
	Texture texture;
	image.loadFromFile("Resources/Textures/CustomButtons.png");
	TransparentGreenScreen(&image);
	texture.loadFromImage(image, IntRect(0, 104, 157, 352));
	Textures.push_back(texture);
	texture.loadFromImage(image, IntRect(157, 104, 157, 352));
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

	String = "Fourier Depth:\n\nSmoothness:\n\nPoints:\n\n     Reset\t\t\t   Draw";
	text.setString(String);
	text.setPosition(DefaultSettingsPosition.x + 10.f, DefaultSettingsPosition.y + 35.f);
	Texts.push_back(text);

	String = '0';
	text.setString(String);
	text.setPosition(DefaultSettingsPosition.x + 100.f, DefaultSettingsPosition.y + 35.f);
	Texts.push_back(text);
	text.setString(String);
	text.setPosition(DefaultSettingsPosition.x + 100.f, DefaultSettingsPosition.y + 64.f);
	Texts.push_back(text);
	text.setString(String);
	text.setPosition(DefaultSettingsPosition.x + 100.f, DefaultSettingsPosition.y + 93.f);
	Texts.push_back(text);

	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112, 3),Vector2i(112,36),Vector2i(112,69) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f,  37.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112,19),Vector2i(112,52),Vector2i(112,85) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f,  49.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112, 3),Vector2i(112,36),Vector2i(112,69) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f,  65.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112,19),Vector2i(112,52),Vector2i(112,85) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f,  77.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112, 3),Vector2i(112,36),Vector2i(112,69) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f,  93.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112,19),Vector2i(112,52),Vector2i(112,85) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f, 105.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(  0, 3),Vector2i(  0,36),Vector2i(  0,69) }), Vector2i(89, 32), Vector2f(.75f,.75f), Vector2f(  7.f - 120.f, 120.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(  0, 3),Vector2i(  0,36),Vector2i(  0,69) }), Vector2i(89, 32), Vector2f(.75f,.75f), Vector2f( 83.f - 120.f, 120.f), false));

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
	Texts[1].setPosition(Sidebar.getPosition().x + 100.f - 7.f * x, Sidebar.getPosition().y + 35.f);
	n = Values[PointsFunction];
	String = std::to_string(n);
	if (n)
		x = (int)(log(n * 1.0001) / log(10));
	else
		x = 0;
	Texts[2].setString(String);
	Texts[2].setPosition(Sidebar.getPosition().x + 100.f - 7.f * x, Sidebar.getPosition().y + 64.f);
	n = Values[FourierPoints];
	String = std::to_string(n);
	if (n)
		x = (int)(log(n * 1.0001) / log(10));
	else
		x = 0;
	Texts[3].setString(String);
	Texts[3].setPosition(Sidebar.getPosition().x + 100.f - 7.f * x, Sidebar.getPosition().y + 93.f);

	
}

void Settings::DrawSettings(Renderer& renderer)
{
	renderer.RenderSprite(Sidebar);
	if (IsOpen) {
		renderer.RenderButtons(Buttons);
		renderer.RenderTexts(Texts);
	}
	
	return;
}

int Settings::SettingsEvents(Vector2i MouseScPos, bool Occupied, bool& PressingButton)
{
	int Change = false;
	Vector2f SidebarPos = Sidebar.getPosition();
	MovementEvents(Change, SidebarPos);
	if (!Occupied && IsOpen)
		MouseEvents(Change, MouseScPos, PressingButton);

	if (Mouse::isButtonPressed(Mouse::Left) && !Occupied) {
		if (buttonCooldown)
			buttonCooldown--;
		if (SettingsIcon(MouseScPos)) {
			if (!buttonCooldown) {
				buttonCooldown = DefaultButtonCooldown;
				PressingButton = true;
				Change = 1;
				if (IsOpen)
					IsOpen = false;
				else
					IsOpen = true;
			}
		}
	}
	else {
		buttonCooldown = 0;
		PressingButton = false;
	}
	return Change;
}
