#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"

#define Pi 3.14159265358979
#define NumOfSeries 3

struct dataset {
	int N;
	double* X;
	double* Y;

	dataset(int n, double* x, double* y) {
		N = n;
		X = x;
		Y = y;
	}
	dataset() {}
};

class Fourier {
private:
	bool Drawing = false;
	PixelFunction F;
	dataset S[3];
	std::vector<Point> Points;
	int Dragging = -1;

	double EvalX(double t);
	double EvalY(double t);

public:

	Fourier() {}
	Fourier(std::vector<int> Values, float* x, float* y);

	void SetDepth(int d);
	void SetPointPosition(int n,  Vector2f Pos);
	void SetPointDescription(int n, bool Des);
	void SetDescriptionsFalse();

	int GetNumberPoints();
	std::vector<int> GetValues();
	bool IsOccupied();
	bool IsDrawing();

	void GenerateS0();
	void GenerateS1();
	void GenerateS2();

	static float Distance2(Vector2f V0, Vector2f V1);

	void CreateDataSet(std::string filename);
	void CreateDataSet(int n, float r = 1.f);
	void AddPointstoDataSet(int Points);
	void GraphFunctionS0(int N);
	void RenderFunction(Renderer& renderer);
	void RenderPoints(Renderer& renderer);
	Vector2f getPosition(int P);

	void FunctionEvents(bool& Change, Vector2f MouseR2, float Scale, std::vector<int> Values);
	int CheckCollision(Vector2f MouseR2, float Scale);
	void Draw();
};