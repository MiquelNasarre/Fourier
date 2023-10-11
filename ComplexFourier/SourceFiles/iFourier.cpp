#include "iFourier.h"

iFourier::iFourier(std::vector<Complex>& points)
	: Points{ points }
{
}

void iFourier::setPoints(std::vector<Complex>& points)
{
	Points = points;
}

void iFourier::setOrder(std::vector<int> order)
{
	Order = order;
}

void iFourier::setTime(float t)
{
	time = t;
	while (time > 1)
		time--;
}

std::vector<Complex>& iFourier::getPoints()
{
	return Points;
}

std::vector<Complex>& iFourier::getCoef()
{
	return Coef;
}

std::vector<int>& iFourier::getOrder()
{
	return Order;
}

std::vector<Complex>& iFourier::getPlot()
{
	return Plot;
}

float iFourier::getTime()
{
	return time;
}

float iFourier::getNorm2()
{
	return Norm2;
}

float iFourier::getdNorm2()
{
	return dNorm2;
}

float iFourier::getddNorm2()
{
	return ddNorm2;
}

Complex iFourier::getCircleCenter(int i)
{
	return eval(2 * Pi * time, i);
}

float iFourier::getCircleRadius(int i)
{
	return Coef[i].abs();
}

float iFourier::norm2(std::vector<Complex> points)
{
	float x = 0;
	int m = points.size();
	for (int i = 0; i < m; i++)
		x += points[i].a * points[i].a + points[i].b * points[i].b;
	return x / m;
}

float iFourier::norm2()
{
	float x = 0;
	int m = Points.size();
	for (int i = 0; i < m; i++)
		x += Points[i].a * Points[i].a + Points[i].b * Points[i].b;
	Norm2 = x / m;
	return Norm2;
}

float iFourier::dnorm2()
{
	std::vector<Complex> dpoints;
	int m = Points.size();
	for (int i = 1; i < m; i++)
		dpoints.push_back((Points[i] - Points[i - 1]) * m / (2 * Pi));
	dNorm2 = norm2(dpoints);
	return dNorm2;
}

float iFourier::ddnorm2()
{
	std::vector<Complex> dpoints;
	int m = Points.size();
	for (int i = 1; i < m; i++)
		dpoints.push_back((Points[i] - Points[i - 1]) * m / (2 * Pi));
	std::vector<Complex> ddpoints;
	m = dpoints.size();
	for (int i = 1; i < m; i++)
		ddpoints.push_back((dpoints[i] - dpoints[i - 1]) * m / (2 * Pi));
	ddNorm2 = norm2(ddpoints);
	return ddNorm2;
}

float iFourier::margin()
{
	Margin = std::abs(ddNorm2 * Norm2 - dNorm2 * dNorm2);
	return Margin;
}

void iFourier::computeLf(float error)
{
	Lf.clear();
	if (error)
		Error = error;
	int l = int(sqrt(dNorm2 / Norm2));
	while (l > 0 && Error * Error * pow(l * l * Norm2 - dNorm2, 2) <= Margin) {
		Lf.push_back(l);
		Lf.push_back(-l);
		l--;
	}
	l = int(sqrt(dNorm2 / Norm2)) + 1;
	while (Error * Error * pow(l * l * Norm2 - dNorm2, 2) <= Margin) {
		Lf.push_back(l);
		Lf.push_back(-l);
		l++;
	}
}

void iFourier::OrderLf()
{
	Order = Lf;
}

void iFourier::fullComputation(float error)
{
	norm2();
	dnorm2();
	ddnorm2();
	margin();
	computeLf(error);
	OrderLf();
	generateCoef();
}

void iFourier::generateCoef()
{
	for (unsigned int i = 0; i < Order.size(); i++) {
		Coef.push_back(Complex(0));
		for (unsigned int j = 0; j < Points.size(); j++)
			Coef[i] += Points[j] * Complex::exp(-I * float(2 * Pi * j * Order[i] / Points.size()));
		Coef[i] = Coef[i] / float(Points.size());
	}
}

void iFourier::generatePlot(int s)
{
	Plot.clear();
	for (int i = 0; i < s; i++) {
		Plot.push_back(eval(2 * Pi * i / s));
	}
	Plot.push_back(Plot[0]);
}

Complex iFourier::eval(float t, unsigned int d)
{
	if (!d)
		d = Order.size();
	Complex a(0);
	for (unsigned int i = 0; i < d; i++)
		a += Coef[i] * Complex::exp(I * Order[i] * t);
	return a;
}

void iFourier::renderPlot(Renderer& renderer)
{
	renderer.RenderPlot(Plot);
}

void iFourier::renderPartialPlot(Renderer& renderer)
{
	int i = int(Plot.size() * time) + 1;
	std::vector<Complex> plot(Plot.begin(), Plot.begin() + i);
	renderer.RenderPlot(plot);
}

void iFourier::renderCircles(Renderer& renderer, float scale)
{
	std::vector<Complex> Circle;
	Complex center, nextcenter(0);
	for (unsigned int i = 0; i < Order.size(); i++) {
		int points = int(CircleSmoothness * Coef[i].abs() * scale);
		if (!points)
			continue;
		if (points > CircleSmoothness)
			points = CircleSmoothness;
		center = nextcenter;
		nextcenter = eval(2 * Pi * time, i + 1);
		Circle.clear();
		
		for (int j = 0; j <= points; j++)
			Circle.push_back(Coef[i] * Complex::exp(I * 2 * Pi * j / points) + center);
		renderer.RenderPlot(Circle, CircleColor);
		renderer.RenderLine(center, nextcenter, LineColor);
		renderer.RenderPoint(nextcenter);
	}
}

void iFourier::renderPoints(Renderer& renderer)
{
	renderer.RenderPoints(Points);
}


