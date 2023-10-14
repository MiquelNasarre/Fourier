#include "NumberBar.h"

NumberBar::NumberBar(std::string Filename, std::vector<Vector2i> TextureLocations, Vector2i Size, Vector2f position, int Max, int Min, int Initial, Font InitialFont) 
	:font{ InitialFont }, Number{ Initial }, Maximum{ Max }, Minimum{ Min }, Position{ position }, Dimensions{ Size }
{
	Image image;
	image.loadFromFile(Filename);
	//TransparentGreenScreen(&image);
	Texture texture;
	texture.loadFromImage(image, IntRect(TextureLocations[0], Size));
	TexHolder.push_back(texture);
	texture.loadFromImage(image, IntRect(TextureLocations[1], Size));
	TexHolder.push_back(texture);
	texture.loadFromImage(image, IntRect(TextureLocations[2], Size));
	TexHolder.push_back(texture);
	Holder.setTexture(TexHolder[0]);
	Holder.setPosition(Position);
	Holder.setScale(1.f, 1.f);
	StrNumber = std::to_string(Number);
	TextNumber.setCharacterSize(14);
	TextNumber.setFillColor(Color::Black);
	TextNumber.setString(StrNumber);
	TextNumber.setFont(font);
	TextNumber.setPosition(Position.x + Dimensions.x - TextNumber.getLocalBounds().width - 4.f, Position.y + 2.f);
}

void NumberBar::setNumber(int number)
{
	Number = number;
	StrNumber = std::to_string(Number);
	TextNumber.setString(StrNumber);
	TextNumber.setPosition(Position.x + Dimensions.x - TextNumber.getLocalBounds().width - 3.f, Position.y + 2.f);
}

void NumberBar::setFont(Font f)
{
}

void NumberBar::setMaximum(int Max)
{
}

void NumberBar::setPosition(Vector2f Position)
{
}

int NumberBar::getNumber()
{
	return Number;
}

Sprite NumberBar::getSprite()
{
	return Holder;
}

int NumberBar::EventCheck(Event& event, Vector2i MousePos)
{
	if (MousePos.x > Position.x && MousePos.y > Position.y && MousePos.x <= Position.x + Dimensions.x && MousePos.x <= Position.x + Dimensions.x && MousePos.y <= Position.y + Dimensions.y) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			SetTexture(Holder, TexHolder[2]);
			Pressed = true;
			JustPressed = true;
		}
		else if (!Pressed)
			SetTexture(Holder, TexHolder[1]);
	}
	else {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Pressed = false;
			SetTexture(Holder, TexHolder[0]);
		}
		else if (!Pressed)
			SetTexture(Holder, TexHolder[0]);
	}
	if (Pressed && event.type == Event::TextEntered) {
		if (JustPressed) {
			setNumber(0);
			JustPressed = false;
		}
			
		if (event.text.unicode >= 48 && event.text.unicode <= 57 && Number * 10 + (int)event.text.unicode - 48 >= Minimum && Number * 10 + (int)event.text.unicode - 48 <= Maximum) {
			Number = Number * 10 + (int)event.text.unicode - 48;
			StrNumber = std::to_string(Number);
			TextNumber.setString(StrNumber);
			TextNumber.setPosition(Position.x + Dimensions.x - TextNumber.getLocalBounds().width - 4.f, Position.y + 2.f);
			return 2;
		}
		else if (event.text.unicode == 8 && StrNumber.size() && Number / 10 >= Minimum && Number / 10 <= Maximum) {
			Number = Number / 10;
			StrNumber = std::to_string(Number);
			TextNumber.setString(StrNumber);
			TextNumber.setPosition(Position.x + Dimensions.x - TextNumber.getLocalBounds().width - 4.f, Position.y + 2.f);
			return 2;
		}
	}
	return 0;
}

void NumberBar::Render(Renderer& renderer)
{

}

void NumberBar::Render(RenderWindow& window)
{
	window.draw(Holder);
	window.draw(TextNumber);
}
