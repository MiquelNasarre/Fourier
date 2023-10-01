#pragma once

#include "Header.h"

#define PointsRadius 4.f
#define PointsColor Color(50,50,50,255)

class Point {
public:
	Vector2f Position;
	float Radius;
	Color color;
	bool Description;

	Point(Vector2f position, float radius = PointsRadius, Color Col = PointsColor, bool description = false) {
		Position = position;
		Radius = radius;
		color = Col;
		Description = description;
	}
};

struct PixelFunction {
	int N;
	float* x = NULL;
	float* y = NULL;
	Color* color = NULL;
};

void TransparentGreenScreen(Image* image);

bool SetTexture(Sprite& sprite, Texture& texture);

bool InsideRectangle(Vector2i MousePos, Vector2f Position, Vector2i Size);

Vector2f IncreaseVector(Vector2f vector, float dx, float dy);

Vector2f AddVectors(Vector2f v0, Vector2f v1);