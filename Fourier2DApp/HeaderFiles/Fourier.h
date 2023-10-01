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

	Color				FunctionColor;
	dataset				Coefficients;
	std::vector<Point>	Points;
	std::string			Name;

	int Dragging = -1;
	bool PointsVisibility = true;
	bool FunctionVisibility = true;

	double EvalX(double t);
	double EvalY(double t);

public:

	void* RandomPointer;

	Fourier(Color color = Color::Red, std::string name = "Untitled") : FunctionColor{color}, Name{ name } { RandomPointer = (void*)(rand() * rand()); }
	Fourier(std::vector<int> Values, float* x, float* y, std::string name, Color color = Color::Red);

	void SetDepth(int d);
	void SetPointPosition(int n,  Vector2f Pos);
	void SetPointDescription(int n, bool Des);
	bool SetDescriptionsFalse();
	void SetFunctionColor(Color Col);
	void SetPointsVisibility(bool T);
	void SetFunctionVisibility(bool T);
	void setName(std::string name);

	dataset* getCoefficients();
	Color GetFunctionColor();
	int GetNumberPoints();
	std::string getName();
	std::vector<int> GetValues();
	bool GetPointsVisibility();
	bool GetFunctionVisibility();
	bool IsOccupied();
	bool IsDrawing();

	void GenerateS0();

	static float Distance2(Vector2f V0, Vector2f V1);

	void CreateDataSet(int n, float r = 1.f);
	void AddPointstoDataSet(int Points);
	void GraphFunctionS0(int N);
	void RenderFunction(Renderer& renderer);
	void RenderPoints(Renderer& renderer);
	Vector2f getPosition(int P);

	void EventCheck(bool& Change, Vector2f MouseR2, float Scale, std::vector<int> Values);
	int CheckCollision(Vector2f MouseR2, float Scale);
	void Draw();
};