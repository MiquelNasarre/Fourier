#include "TimeFourier.h"

float TimeFourier::EvalX(float theta)
{
	float x0 = (float)Coefficients[Current0]->X[0];
	float x1 = (float)Coefficients[Current1]->X[0];
	for (int i = 1; i < Coefficients[Current0]->N; i++)
		x0 += float(Coefficients[Current0]->X[i] * sin(i * theta) + Coefficients[Current0]->X[i + Coefficients[Current0]->N] * cos(i * theta));
	for (int i = 1; i < Coefficients[Current1]->N; i++)
		x1 += float(Coefficients[Current1]->X[i] * sin(i * theta) + Coefficients[Current1]->X[i + Coefficients[Current1]->N] * cos(i * theta));
	return x0 * (1 - time) + x1 * time;
}

float TimeFourier::EvalY(float theta)
{
	float y0 = (float)Coefficients[Current0]->Y[0];
	float y1 = (float)Coefficients[Current1]->Y[0];
	for (int i = 1; i < Coefficients[Current0]->N; i++)
		y0 += float(Coefficients[Current0]->Y[i] * sin(i * theta) + Coefficients[Current0]->Y[i + Coefficients[Current0]->N] * cos(i * theta));
	for (int i = 1; i < Coefficients[Current1]->N; i++)
		y1 += float(Coefficients[Current1]->Y[i] * sin(i * theta) + Coefficients[Current1]->Y[i + Coefficients[Current1]->N] * cos(i * theta));
	return y0 * (1 - time) + y1 * time;
}

Color TimeFourier::currentColor()
{
	unsigned char R = (unsigned char)(FunctionColors[Current0].r * (1 - time) + FunctionColors[Current1].r * time);
	unsigned char G = (unsigned char)(FunctionColors[Current0].g * (1 - time) + FunctionColors[Current1].g * time);
	unsigned char B = (unsigned char)(FunctionColors[Current0].b * (1 - time) + FunctionColors[Current1].b * time);
	unsigned char A = (unsigned char)(FunctionColors[Current0].a * (1 - time) + FunctionColors[Current1].a * time);
	return Color(R,G,B,255);
}

int TimeFourier::getSize()
{
	return Coefficients.size();
}

void TimeFourier::setSmoothness(int s)
{
	CurrentPlot.N = s;
	CurrentPlot.x = (float*)calloc(sizeof(float), s);
	CurrentPlot.y = (float*)calloc(sizeof(float), s);
	CurrentPlot.color = (Color*)calloc(sizeof(Color), s);
}

void TimeFourier::AddCoefficients(dataset* New, Color color)
{
	Coefficients.push_back(New);
	FunctionColors.push_back(color);
	Change();
}

void TimeFourier::deleteCoefficients(int n)
{
	Coefficients.erase(Coefficients.begin() + n);
	Change();
	if (Current0 >= n)
		Current0--;
	if (Current1 >= n)
		Current1--;
}

void TimeFourier::deleteAll()
{
	Coefficients.clear();
	FunctionColors.clear();
	Change();
}

void TimeFourier::StopTime()
{
	Playing = false;
}

void TimeFourier::StartTime()
{
	if (Coefficients.size() < 2)
		return;
	Playing = true;
	itime = (float)clock();
}

void TimeFourier::Restart()
{
	time = 0;
	itime = (float)clock();
	Current0 = 0;
	Current1 = 1;
	Change();
}

void TimeFourier::Change()
{
	changes = true;
}

bool TimeFourier::UpdatePlot()
{
	if ((!Playing && !changes) || Coefficients.size() < 2)
		return false;
	time = ((float)clock() - itime) * speed / CLOCKS_PER_SEC;
	while (time > 1) {
		Current0 = (Current0 + 1) % Coefficients.size();
		Current1 = (Current1 + 1) % Coefficients.size();
		time--;
		itime += CLOCKS_PER_SEC;
	}

	Color col = currentColor();
	for (int i = 0; i < CurrentPlot.N; i++) {
		CurrentPlot.x[i] = EvalX(2 * i * (float)Pi / (CurrentPlot.N - 1));
		CurrentPlot.y[i] = EvalY(2 * i * (float)Pi / (CurrentPlot.N - 1));
		CurrentPlot.color[i] = col;
	}
	return true;
}

void TimeFourier::Render(Renderer& renderer)
{
	if (Coefficients.size() >= 2)
		renderer.RenderFunction(CurrentPlot);
}
