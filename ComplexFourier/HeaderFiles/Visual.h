#pragma once

#include "Header.h"
#include "Renderer.h"
#include "iFourier.h"
#include "Button.h"
#include "Settings.h"

#ifdef DarkTheme
	#define BackgroundColor Color::Black
	#define DataColor		Color::White
#else
	#define BackgroundColor Color::White
	#define DataColor		Color::Black
#endif

#define FunctionSmoothness	2000
#define ScreenWidth			1180
#define ScreenHeight		640
#define speedMult			1.2f

#define dataWindowWidth		500
#define dataWindowHeight	300
#define HorizontalMargin	40.f
#define VerticalMargin		32.f

class Visual {
private:
	RenderWindow window;
	RenderWindow dataWindow;
	Renderer renderer;
	Renderer DataRenderer;
	View view;
	iFourier fourier;

	Settings settings;

	bool Plain = false;
	int CircleView = 0;
	bool pressing = false;
	Vector2i MouseTracker;
	Complex PrevCenter;
	float speed = 0.001f;

	bool drawing = false;
	std::vector<Complex> canva;

public:
	Visual();

	Vector2i mousePosition();

	void createDataWindow();
	void eventsDataWindow();
	void drawingEvents();

	void computeFourier();

	void eventCheck();
	void render();
	void mainLoop();
};