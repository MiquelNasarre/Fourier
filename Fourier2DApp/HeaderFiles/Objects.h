#pragma once

#include "Header.h"

#define IncreaseDepthButton			0
#define DecreaseDepthButton			1
#define IncreaseSmoothnessButton	2
#define DecreaseSmoothnessButton	3
#define IncreasePointsButton		4
#define DecreasePointsButton		5
#define ResetButton					6
#define DrawButton					7

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
	bool Description = false;
};

struct ButtonStr {
	Vector2f Position;
	Vector2f Dimensions;
	RGBA Color;
	unsigned char Texture;
	float Scale;
	
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
	Button(){}

	void setPosition(Vector2f Pos);
	void setPosition(float x, float y);
	void IncreasePosition(Vector2f Diff);
	void IncreasePosition(float dx, float dy);
	void setScale(Vector2f Pos);
	void setScale(float x, float y);
};

class Objects {
private:
	CircleStr*		Circles;
	ButtonStr*	Rectangles;
	PixelFunction*	Functions;
	std::vector<Button> Buttons;
	
public:
	int NumOfCircles;
	int NumOfButtons;
	int NumOfFunctions = 0;

	void InitializeCircles(int N, float* Radius, float* Xs, float* Ys, RGBA* Col);
	void SetCirclePos(int n, float x, float y);
	void SetCircleRadius(int n, float r);
	void SetCircleColor(int n, RGBA c);
	void SetCircleDescription(int n, bool d);
	void SetDescriptionsFalse();

	Vector2f GetCirclePos(int n);
	float GetCircleRadius(int n);
	RGBA GetCircleColor(int n);
	bool GetCircleDescription(int n);

	void InitializeButtons();
	Button* getButton(int i);

	void AddFunction(int n, float* x, float* y, RGBA* Col);
	void ModifyFunction(int N, int n, float* x, float* y, RGBA* Col);
	PixelFunction* GetFunction(int n);
	static void TransparentGreenScreen(Image* image);

};