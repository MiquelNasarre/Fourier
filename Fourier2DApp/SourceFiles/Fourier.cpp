#include "Fourier.h"

Fourier::Fourier(std::vector<int> Values, float* x, float* y, std::string name, Color color) : Name{ name }, FunctionColor{ color }
{
	for (int i = 0; i < Values[0]; i++)
		Points.push_back(Point(Vector2f(x[i], y[i])));
	Coefficients.N = Values[2];
	GenerateS0();
	GraphFunctionS0(Values[1]);

	RandomPointer = (void*)(rand() * rand());
}

void Fourier::SetDepth(int d)
{
	for (int i = 0; i < NumOfSeries; i++) {
		Coefficients.N = d;
	}
	return;
}

void Fourier::SetPointPosition(int n, Vector2f Pos)
{
	Points[n].Position = Pos;
}

void Fourier::SetPointDescription(int n, bool Des)
{
	Points[n].Description = Des;
}

bool Fourier::SetDescriptionsFalse()
{
	for (int i = 0; i < (int)Points.size(); i++) {
		if (Points[i].Description) {
			Points[i].Description = false;
			return true;
		}
	}
	return false;
}

void Fourier::SetFunctionColor(Color Col)
{
	FunctionColor = Col;
}

void Fourier::SetPointsVisibility(bool T)
{
	PointsVisibility = T;
}

void Fourier::SetFunctionVisibility(bool T)
{
	FunctionVisibility = T;
}

void Fourier::setName(std::string name)
{
	Name = name;
}

void Fourier::ResetRandomPointer()
{
	RandomPointer = (void*)(rand() * rand());
}

dataset* Fourier::getCoefficients()
{
	return &Coefficients;
}

Color Fourier::GetFunctionColor()
{
	return FunctionColor;
}

int Fourier::GetNumberPoints()
{
	return Points.size();
}

std::string Fourier::getName()
{
	return Name;
}

std::vector<int> Fourier::GetValues()
{
	return std::vector<int>({(int)Points.size(),F.N,Coefficients.N});
}

std::vector<Point>* Fourier::GetPoints()
{
	return &Points;
}

bool Fourier::GetPointsVisibility()
{
	return PointsVisibility;
}

bool Fourier::GetFunctionVisibility()
{
	return FunctionVisibility;
}

bool Fourier::IsOccupied()
{
	if (Dragging >= 0)
		return true;
	return false;
}

bool Fourier::IsDrawing()
{
	return Drawing;
}

double Fourier::EvalX(double t)
{
	double x = Coefficients.X[0];
	for (int i = 1; i < Coefficients.N; i++) {
		x += Coefficients.X[i] * sin(i * t) + Coefficients.X[i + Coefficients.N] * cos(i * t);
	}
	return x;
}

double Fourier::EvalY(double t)
{
	double y = Coefficients.Y[0];
	for (int i = 1; i < Coefficients.N; i++) {
		y += Coefficients.Y[i] * sin(i * t) + Coefficients.Y[i + Coefficients.N] * cos(i * t);
	}
	return y;
}

float Fourier::Distance2(Vector2f V0, Vector2f V1)
{
	return (V1.x - V0.x) * (V1.x - V0.x) + (V1.y - V0.y) * (V1.y - V0.y);
}

void Fourier::GenerateS0()
{	
	int N = Points.size();
	Coefficients.X = (double*)calloc(Coefficients.N * sizeof(double), 2);
	Coefficients.Y = (double*)calloc(Coefficients.N * sizeof(double), 2);
	for (int n = 0; n < Coefficients.N; n++) {
		for (int i = 0; i < N; i++) {
			if (n == 0) {
				Coefficients.X[n] += 1. / N * Points[i].Position.x;
				Coefficients.Y[n] += 1. / N * Points[i].Position.y;
			}
			else {
				Coefficients.X[n] += 2. / N * Points[i].Position.x * sin(2 * Pi * i * n / N);
				Coefficients.X[n + Coefficients.N] += 2. / N * Points[i].Position.x * cos(2 * Pi * i * n / N);
				Coefficients.Y[n] += 2. / N * Points[i].Position.y * sin(2 * Pi * i * n / N);
				Coefficients.Y[n + Coefficients.N] += 2. / N * Points[i].Position.y * cos(2 * Pi * i * n / N);
			}
		}
	}
}

void Fourier::CreateDataSet(int n, float r)
{
	Drawing = false;
	Points.clear();
	for (int i = 0; i < n; i++)
		Points.push_back(Point(Vector2f(r * (float)cos(2 * Pi / n * i), r * (float)sin(2 * Pi / n * i))));
}

void Fourier::AddPointstoDataSet(int Pts)
{
	if (Drawing)
		return;
	Points.clear();
	for (int i = 0; i < Pts; i++)
		Points.push_back(Point(Vector2f((float)EvalX(2 * i * Pi / Pts), (float)EvalY(2 * i * Pi / Pts))));
}

void Fourier::GraphFunctionS0(int N)
{
	F.N = N;
	F.x = (float*)calloc(sizeof(float), N);
	F.y = (float*)calloc(sizeof(float), N);
	F.color = (Color*)calloc(sizeof(Color), N);
	for (int i = 0; i < N; i++) {
		F.x[i] = (float)EvalX(2 * i * Pi / (N - 1));
		F.y[i] = (float)EvalY(2 * i * Pi / (N - 1));
		F.color[i] = FunctionColor;
	}
}

void Fourier::RenderFunction(Renderer& renderer)
{
	if (Drawing)
		return;
	renderer.RenderFunction(F);
}

void Fourier::RenderPoints(Renderer& renderer)
{
	for (int i = 0; i < (int)Points.size(); i++)
		renderer.RenderPoint(Points[i], i);
}

Vector2f Fourier::getPosition(int P)
{
	return Points[P].Position;
}

void Fourier::EventCheck(bool& Change, Vector2f MouseR2, float Scale, std::vector<int> Values)
{
	int Object = CheckCollision(MouseR2, Scale);
	if (Drawing) {
		if (Points.size()) {
			Points[0].color = Color::Blue;
			Points[0].Radius = PointsRadius + 1.f;
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (Dragging >= 0) {
				Points[Dragging].Position = MouseR2;
				Change = true;
			}
			else {
				if (Dragging == -3);
				else if (Points.size() > 3 && Object == 0) {
					Drawing = false;
					Points[0].color = PointsColor;
					Points[0].Radius = PointsRadius;
					return;
				}
				else {
					Points.push_back(Point(MouseR2));
					Dragging = Points.size() - 1;
					Points[Dragging].Description = true;
					Change = true;
				}
			}
		}
		else if (Dragging != -1) {
			SetDescriptionsFalse();
			Dragging = -1;
			Change = true;
		}
		return;
	}
	Coefficients.N = Values[2];
	F.N = Values[1];

	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (Dragging == -2);
		else if (Dragging >= 0) {
			SetPointPosition(Dragging, MouseR2);
			Change = true;
		}
		else {
			if (Object >= 0) {
				SetPointPosition(Object, MouseR2);
				Dragging = Object;
				Change = true;
			}
			else
				Dragging = -2;

		}
	}
	else {
		Dragging = -1;
		if (Object >= 0) {
			SetPointDescription(Object, true);
			Change = true;
		}
		else if (SetDescriptionsFalse())
			Change = true;
	}
	if (F.color && FunctionColor != F.color[0])
		Change = true;
	if (Change) {
		GenerateS0();
		GraphFunctionS0(F.N);
	}
}

int Fourier::CheckCollision(Vector2f MouseR2, float Scale)
{
	for (int i = 0; i < (int)Points.size(); i++) {
		if (Distance2(MouseR2, Points[i].Position) < pow(PointsRadius / Scale, 2))
			return i;
	}
	return -1;
}

void Fourier::Draw()
{
	Drawing = true;
	PointsVisibility = true;
	Points.clear();
	Dragging = -3;
}

