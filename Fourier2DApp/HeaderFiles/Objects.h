#pragma once

#include "Header.h"

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

struct CircleStr {
	Vector2f Position;
	float Radius;
	RGBA Color;
};

struct RectangleStr {
	Vector2f Position;
	Vector2f Dimensions;
	RGBA Color;
};

struct PixelFunction {
	int N;
	float* x;
	float* y;
	RGBA* Color;
};

class Objects {
private:
	CircleStr*		Circles;
	RectangleStr*	Rectangles;
	PixelFunction*	Functions;
	
public:
	int NumOfCircles;
	int NumOfRectangles;
	int NumOfFunctions = 0;

	void InitializeCircles(int N, float* Radius, float* Xs, float* Ys, RGBA* Col);
	void SetCirclePos(int n, float x, float y);
	void SetCircleRadius(int n, float r);
	void SetCircleColor(int n, RGBA c);

	Vector2f GetCirclePos(int n);
	float GetCircleRadius(int n);
	RGBA GetCircleColor(int n);


	void InitializeRectangles(int N, float* Width, float* Height, float* Xs, float* Ys, RGBA* Col);
	void SetRectanglePos(int n, float x, float y);
	void SetRectangleDimensions(int n, Vector2f Dim);
	void SetRectangleColor(int n, RGBA c);

	Vector2f GetRectanglePos(int n);
	Vector2f GetRectangleDimensions(int n);
	RGBA GetRectangleColor(int n);

	void AddFunction(int n, float* x, float* y, RGBA* Col);
	void ModifyFunction(int N, int n, float* x, float* y, RGBA* Col);
	PixelFunction* GetFunction(int n);

};