#pragma once

#include "Header.h"

#define PointsRadius 4.f
#define PointsColor Color(50,50,50,255)

//struct RGBA {
//	unsigned char R = 0;
//	unsigned char G = 0;
//	unsigned char B = 0;
//	unsigned char A = 255;
//
//	RGBA() {}
//	RGBA(unsigned char r, unsigned char g, unsigned char b) {
//		R = r;
//		G = g;
//		B = b;
//		A = 255;
//	}
//	RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
//		R = r;
//		G = g;
//		B = b;
//		A = a;
//	}
//	RGBA(char Col) {
//		if (Col == 'R') {
//			R = 255;
//			G = 0;
//			B = 0;
//			A = 255;
//			return;
//		}
//		if (Col == 'G') {
//			R = 0;
//			G = 255;
//			B = 0;
//			A = 255;
//			return;
//		}
//		if (Col == 'B') {
//			R = 0;
//			G = 0;
//			B = 255;
//			A = 255;
//			return;
//		}
//		if (Col == 'W') {
//			R = 255;
//			G = 255;
//			B = 255;
//			A = 255;
//			return;
//		}
//		if (Col == 'K') {
//			R = 0;
//			G = 0;
//			B = 0;
//			A = 255;
//			return;
//		}
//		if (Col == 'T') {
//			R = 0;
//			G = 0;
//			B = 0;
//			A = 0;
//			return;
//		}
//		if (Col == 'Y') {
//			R = 255;
//			G = 255;
//			B = 0;
//			A = 255;
//			return;
//		}
//		if (Col == 'g') {
//			R = 50;
//			G = 50;
//			B = 50;
//			A = 255;
//			return;
//		}
//		return;
//	}
//};

class Point {
public:
	Vector2f Position;
	float Radius;
	Color color;
	bool Description;

	Point(){}
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