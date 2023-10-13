#include "Header.h"

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

bool InsideCircle(Vector2i MousePos, Vector2f Position, int radius)
{
	if ((MousePos.x - Position.x) * (MousePos.x - Position.x) + (MousePos.y - Position.y) * (MousePos.y - Position.y) < radius * radius)
		return true;
	return false;
}

Vector2f operator+(const Vector2f& v0, const Vector2f& v1)
{
	return Vector2f(v0.x + v1.x, v0.y + v1.y);
}

Vector2i operator+(const Vector2i& v0, const Vector2i& v1)
{
	return Vector2i(v0.x + v1.x, v0.y + v1.y);
}

Vector2f operator*(const Vector2f& v0, const Vector2f& v1) {
	return Vector2f(v0.x * v1.x, v0.y * v1.y);
}

Vector2f operator*(const Vector2f& v0, const float& x)
{
	return Vector2f(v0.x * x, v0.y * x);
}

Vector2f operator/(const Vector2f& v0, const float& x)
{
	return Vector2f(v0.x / x, v0.y / x);
}
