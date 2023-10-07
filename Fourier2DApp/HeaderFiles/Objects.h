#pragma once

#include "Header.h"

#define PointsRadius 4.f
#define PointsColor Color(50, 50, 50, 255)

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

struct BlenderSave {
	std::vector<int> Order;
	float speed;
	std::string Name;
};

struct SaveState {
	static const int FourierLocated = 0;
	static const int BlenderLocated = 1;

	static const int Modify = 0;
	static const int Create	= 1;
	static const int Delete	= 2;

	int Location;
	int Nature;
	int Identifier;

	std::vector<Vector2f>	Fourier;
	std::vector<int> Values;
	Color FourierColor;
	std::string Name;

	std::vector<BlenderSave> Blenders;

	SaveState(int nature, int identifier, std::vector<Point> points = std::vector<Point>{}, Color color = Color(), std::vector<int> values = std::vector<int>{}, std::string name = "");
};

void TransparentGreenScreen(Image* image);

bool SetTexture(Sprite& sprite, Texture& texture);

bool InsideRectangle(Vector2i MousePos, Vector2f Position, Vector2i Size);

Vector2f IncreaseVector(Vector2f vector, float dx, float dy);

Vector2f AddVectors(Vector2f v0, Vector2f v1);

Vector2i AddVectors(Vector2i v0, Vector2i v1);

Vector2i AddVectors(Vector2i v0, Vector2i v1, Vector2i v2);