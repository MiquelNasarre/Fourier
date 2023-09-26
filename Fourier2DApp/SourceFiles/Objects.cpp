#include "Objects.h"

Button::Button(std::string TextureFile, std::vector<Vector2i> PosInFile, Vector2i SizeInFile, Vector2f scale, Vector2f position, bool Draw) {
	ToBe = Draw;
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
}

void Button::setPosition(Vector2f Pos)
{
	Position = Pos;
	sprite.setPosition(Position);
}

void Button::setPosition(float x, float y)
{
	Position = Vector2f(x, y);
	sprite.setPosition(Position);
}

void Button::IncreasePosition(Vector2f Diff) 
{
	Position = Vector2f(Position.x + Diff.x, Position.y + Diff.y);
	sprite.setPosition(Position);
}

void Button::IncreasePosition(float dx, float dy) 
{
	Position = Vector2f(Position.x + dx, Position.y + dy);
	sprite.setPosition(Position);
}

void Button::setScale(Vector2f scale) 
{
	Dimensions = Vector2f(Dimensions.x * scale.x / Scale.x, Dimensions.y * scale.y / Scale.y);
	Scale = scale;
}

void Button::setScale(float x, float y) 
{
	Dimensions = Vector2f(Dimensions.x * x / Scale.x, Dimensions.y * y / Scale.y);
	Scale = Vector2f(x, y);
}

bool Button::IsinPos(Vector2i MouseScPos)
{
	if ((float)MouseScPos.x > Position.x &&
		(float)MouseScPos.y > Position.y &&
		(float)MouseScPos.x <= Position.x + Dimensions.x &&
		(float)MouseScPos.y <= Position.y + Dimensions.y)
		return true;
	return false;
}

void TransparentGreenScreen(Image* image)
{
	for (unsigned int i = 0; i < image->getSize().x; i++) {
		for (unsigned int j = 0; j < image->getSize().y; j++) {
			if (image->getPixel(i, j) == Color(0, 255, 0, 255)) {
				image->setPixel(i, j, Color::Transparent);
			}
		}
	}
}
