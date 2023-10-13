#include "Button.h"

Button::Button(std::string TextureFile, std::vector<Vector2i> PosInFile, Vector2i SizeInFile, Vector2f scale, Vector2f position, bool Draw, std::string textStr, Vector2f textPosition, Font font, int CharacterSize, Color FillColor)
	: Visibility{ Draw }, Position{ position }, Scale{ scale }, Dimensions{ Vector2f(Scale.x * SizeInFile.x, Scale.y * SizeInFile.y) }, textFont{ font }, textPos{ textPosition }
{
	Visibility = Draw;
	Position = position;
	Scale = scale;
	Dimensions = Vector2f(Scale.x * SizeInFile.x, Scale.y * SizeInFile.y);

	Image image;
	Texture texture;
	image.loadFromFile(TextureFile);
	TransparentGreenScreen(&image);
	for (int i = 0; i < NumOfTexturesButtons; i++) {
		texture.loadFromImage(image, IntRect(PosInFile[i], SizeInFile));
		Textures.push_back(texture);
	}
	sprite.setTexture(Textures[0]);
	sprite.setScale(Scale);
	sprite.setPosition(position);

	text.setCharacterSize(CharacterSize);
	text.setFont(textFont);
	text.setFillColor(FillColor);
	text.setString(textStr);
	text.setPosition(Position.x + textPos.x, Position.y + textPos.y);
}

Button::Button(const Button& other)
{
	Position = other.Position;
	Dimensions = other.Dimensions;
	Textures = other.Textures;
	sprite = other.sprite;
	Scale = other.Scale;
	State = other.State;
	Visibility = other.Visibility;
	sprite.setTexture(Textures[0]);
	textFont = other.textFont;
	textPos = other.textPos;
	text = other.text;
	text.setFont(textFont);
	text.setPosition(other.text.getPosition());
	text.setString(other.text.getString());
	text.setFillColor(other.text.getFillColor());
}

Vector2f Button::GetPosition()
{
	return Position;
}

Vector2f Button::GetDimensions()
{
	return Dimensions;
}

int Button::GetState()
{
	return State;
}

bool Button::GetVisibility()
{
	return Visibility;
}

void Button::setPosition(Vector2f Pos)
{
	Position = Pos;
	sprite.setPosition(Position);
	text.setPosition(Pos.x + textPos.x, Pos.y + textPos.y);
}

void Button::setPosition(float x, float y)
{
	Position = Vector2f(x, y);
	sprite.setPosition(Position);
	text.setPosition(x + textPos.x, y + textPos.y);
}

void Button::IncreasePosition(Vector2f Diff)
{
	Position = Vector2f(Position.x + Diff.x, Position.y + Diff.y);
	sprite.setPosition(Position);
	text.setPosition(Position.x + textPos.x, Position.y + textPos.y);
}

void Button::IncreasePosition(float dx, float dy)
{
	Position = Vector2f(Position.x + dx, Position.y + dy);
	sprite.setPosition(Position);
	text.setPosition(Position.x + textPos.x, Position.y + textPos.y);
}

void Button::setState(int s)
{
	State = s;
	if (s == 1 || s == -1)
		SetTexture(sprite, Textures[0]);
	if (s == 2 || s == -2)
		SetTexture(sprite, Textures[1]);
	if (s == 3 || s == -3)
		SetTexture(sprite, Textures[2]);
}

void Button::setVisibility(bool V)
{
	Visibility = V;
}

void Button::setTexture(int t)
{
	SetTexture(sprite, Textures[t]);
	State = t + 1;
}

void Button::setColor(Color color)
{
	if (sprite.getColor() != color)
		sprite.setColor(color);
}

void Button::setTextures(std::vector<Texture> textures)
{
	Textures = textures;
}

void Button::setFont(Font font)
{
	textFont = font;
}

void Button::setString(std::string String)
{
	text.setString(String);
}

int Button::eventCheck(Vector2i MouseScPos)
{
	if (InsideRectangle(MouseScPos,Position,(Vector2i)Dimensions)) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (State == 3 || State == -3)
				State = -3;
			else {
				State = 3;
				sprite.setTexture(Textures[2]);
			}
		}
		else {
			if (State == 2 || State == -2)
				State = -2;
			else {
				State = 2;
				sprite.setTexture(Textures[1]);
			}
		}
	}
	else {
		if (State == 1 || State == -1) {
			if (SetTexture(sprite, Textures[0]))
				State = 1;
			else
				State = -1;
		}
			
		else {
			State = 1;
			sprite.setTexture(Textures[0]);
		}
	}
	return State;
}

void Button::Render(RenderWindow& window)
{
	if (Visibility) {
		window.draw(sprite);
		if (text.getString().getSize())
			window.draw(text);
	}	
}
