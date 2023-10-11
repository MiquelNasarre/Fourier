#pragma once

#include "Header.h"
#include "Renderer.h"
#include "iFourier.h"
#include "Button.h"
#include "Settings.h"

#ifdef DarkTheme
	#define BackgroundColor Color::Black
#else
	#define BackgroundColor Color::White
#endif

#define FunctionSmoothness 1000
#define ScreenWidth     1180
#define ScreenHeight    640

class Visual {
private:
	RenderWindow window;
	RenderWindow dataWindow;
	Renderer renderer;
	Renderer DataRenderer;
	iFourier fourier;

	Settings settings;

	bool Plain = false;
	int CircleView = 0;
	bool pressing = false;
	Vector2i MouseTracker;
	Complex PrevCenter;

public:
	Visual();

	Vector2i mousePosition();

	void createDataWindow();
	void eventsDataWindow();


	void eventCheck();
	void render();
	void mainLoop();
};