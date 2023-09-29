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
	float* x;
	float* y;
	Color* color;
};

void TransparentGreenScreen(Image* image);

bool SetTexture(Sprite& sprite, Texture& texture);

bool InsideRectangle(Vector2i MousePos, Vector2f Position, Vector2i Size);

Vector2f IncreaseVector(Vector2f vector, float dx, float dy);