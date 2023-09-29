#include "Objects.h"

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

bool SetTexture(Sprite& sprite, Texture& texture)
{
	if (sprite.getTexture() == &texture)
		return false;
	sprite.setTexture(texture);
	return true;
}

bool InsideRectangle(Vector2i MousePos, Vector2f Position, Vector2i Size)
{
	if (MousePos.x > Position.x &&
		MousePos.y > Position.y &&
		MousePos.x <= Position.x + Size.x &&
		MousePos.y <= Position.y + Size.y)
		return true;
	return false;
}

Vector2f IncreaseVector(Vector2f vector, float dx, float dy)
{
	return Vector2f(vector.x + dx, vector.y + dy);
}

