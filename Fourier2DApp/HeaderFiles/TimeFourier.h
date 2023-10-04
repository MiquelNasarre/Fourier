#pragma once

#include "Header.h"
#include "Fourier.h"
#include "Objects.h"
#include "Renderer.h"

class TimeFourier {
private:

	std::vector<dataset*>	Coefficients;
	std::vector<Color>		FunctionColors;

	float time = 0, itime = 0, speed = 1.f;
	bool Playing = false;
	bool changes = true;
	PixelFunction CurrentPlot;
	int Current0 = 0, Current1 = 1;

	float EvalX(float theta);
	float EvalY(float theta);
	
	Color currentColor();

public:

	int getSize();
	float getSpeed();
	bool isPlaying();

	void setCurrent(int n);
	void setSpeed(float s);
	void setSmoothness(int s);
	void AddCoefficients(dataset* New, Color color);
	void deleteCoefficients(int n);
	void deleteAll();
	void StopTime();
	bool StartTime();
	void Restart();
	void Change();
	void Back();
	void Forward();
	void IncreaseSpeed(float x);

	bool UpdatePlot();
	void Render(Renderer& renderer);
};
