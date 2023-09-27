#pragma once

#include "Header.h"

#define PointsRadius 4.f
#define PointsColor RGBA('g')

struct RGBA {
	unsigned char R = 0;
	unsigned char G = 0;
	unsigned char B = 0;
	unsigned char A = 255;

	RGBA() {}
	RGBA(unsigned char r, unsigned char g, unsigned char b) {
		R = r;
		G = g;
		B = b;
		A = 255;
	}
	RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		R = r;
		G = g;
		B = b;
		A = a;
	}
	RGBA(char Col) {
		if (Col == 'R') {
			R = 255;
			G = 0;
			B = 0;
			A = 255;
			return;
		}
		if (Col == 'G') {
			R = 0;
			G = 255;
			B = 0;
			A = 255;
			return;
		}
		if (Col == 'B') {
			R = 0;
			G = 0;
			B = 255;
			A = 255;
			return;
		}
		if (Col == 'W') {
			R = 255;
			G = 255;
			B = 255;
			A = 255;
			return;
		}
		if (Col == 'K') {
			R = 0;
			G = 0;
			B = 0;
			A = 255;
			return;
		}
		if (Col == 'T') {
			R = 0;
			G = 0;
			B = 0;
			A = 0;
			return;
		}
		if (Col == 'Y') {
			R = 255;
			G = 255;
			B = 0;
			A = 255;
			return;
		}
		if (Col == 'g') {
			R = 50;
			G = 50;
			B = 50;
			A = 255;
			return;
		}
		return;
	}
};

class Point {
public:
	Vector2f Position;
	float Radius;
	RGBA Color;
	bool Description;

	Point(){}
	Point(Vector2f position, float radius = PointsRadius, RGBA color = PointsColor, bool description = false) {
		Position = position;
		Radius = radius;
		Color = color;
		Description = description;
	}
};

struct PixelFunction {
	int N;
	float* x;
	float* y;
	RGBA* Color;
};

class Button {
public:
	Vector2f Position;
	Vector2f Dimensions;
	std::vector<Texture> Textures;
	Sprite sprite;
	Vector2f Scale;
	int State = 0;
	bool ToBe;

	Button(std::string TextureFile, std::vector<Vector2i> PosInFile, Vector2i SizeInFile, Vector2f scale, Vector2f position = Vector2f(0.f, 0.f), bool Draw = true);
	Button();

	void setPosition(Vector2f Pos);
	void setPosition(float x, float y);
	void IncreasePosition(Vector2f Diff);
	void IncreasePosition(float dx, float dy);
	void setScale(Vector2f Pos);
	void setScale(float x, float y);
	bool IsinPos(Vector2i MouseScPos);
};



void TransparentGreenScreen(Image* image);