#include "Objects.h"

void Objects::InitializeCircles(int N, float* Radius, float* Xs, float* Ys, RGBA* Col)
{
	NumOfCircles = N;
	Circles = (CircleStr*)calloc(sizeof(CircleStr), N);
	for (int i = 0; i < N; i++) {
		Circles[i].Radius = Radius[i];
		Circles[i].Position.x = Xs[i];
		Circles[i].Position.y = Ys[i];
		Circles[i].Color = Col[i];
	}

}

void Objects::SetCirclePos(int n, float x, float y)
{
	Circles[n].Position.x = x;
	Circles[n].Position.y = y;
	return;
}

void Objects::SetCircleRadius(int n, float r)
{
	Circles[n].Radius = r;
	return;
}

void Objects::SetCircleColor(int n, RGBA c)
{
	Circles[n].Color = c;
	return;
}

Vector2f Objects::GetCirclePos(int n)
{
	return Circles[n].Position;
}

float Objects::GetCircleRadius(int n)
{
	return Circles[n].Radius;
}

RGBA Objects::GetCircleColor(int n)
{
	return Circles[n].Color;
}

void Objects::InitializeRectangles(int N, float* Width, float* Height, float* Xs, float* Ys, RGBA* Col)
{
	NumOfRectangles = N;
	Rectangles = (RectangleStr*)calloc(sizeof(RectangleStr), N);
	for (int i = 0; i < N; i++) {
		Rectangles[i].Position.x = Xs[i];
		Rectangles[i].Position.y = Ys[i];
		Rectangles[i].Dimensions.x = Width[i];
		Rectangles[i].Dimensions.y = Height[i];
		Rectangles[i].Color = Col[i];
	}
}

void Objects::SetRectanglePos(int n, float x, float y)
{
	Rectangles[n].Position.x = x;
	Rectangles[n].Position.y = y;
	return;
}

void Objects::SetRectangleDimensions(int n, Vector2f Dim)
{
	Rectangles[n].Dimensions = Dim;
	return;
}

void Objects::SetRectangleColor(int n, RGBA c)
{
	Rectangles[n].Color = c;
	return;
}

Vector2f Objects::GetRectanglePos(int n)
{
	return Rectangles[n].Position;
}

Vector2f Objects::GetRectangleDimensions(int n)
{
	return Rectangles[n].Dimensions;
}

RGBA Objects::GetRectangleColor(int n)
{
	return Rectangles[n].Color;
}

void Objects::AddFunction(int n, float* x, float* y, RGBA* Col) {
	int N = NumOfFunctions++;
	Functions = (PixelFunction*)realloc(Functions, sizeof(PixelFunction) * NumOfFunctions);
	Functions[N].N = n;
	Functions[N].Color = Col;
	Functions[N].x = x;
	Functions[N].y = y;
}

void Objects::ModifyFunction(int N, int n, float* x, float* y, RGBA* Col)
{
	Functions[N].N = n;
	Functions[N].Color = Col;
	Functions[N].x = x;
	Functions[N].y = y;
}

PixelFunction* Objects::GetFunction(int n)
{
	return &Functions[n];
}
