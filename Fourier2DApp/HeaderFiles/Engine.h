#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"
#include "2dFourier.h"

#define PointsColor RGBA('g')
#define PointsRadius 4.f
#define StdKeyCooldown 8
#define StdButtonCooldown 4
#define DefaultSettingsPosition Vector2f(-120.f, 5.f)
#define DefaultInitialPoints 50
#define DefaultPointsFunction 500
#define DefaultFourierDepth 10


class Engine {
private:
	int InitialPoints = DefaultInitialPoints;
	int PointsFunction = DefaultPointsFunction;
	int FourierDepth = DefaultFourierDepth;
	int KeyCooldown = 0;
	int ButtonCooldown = 0;
	int Dragging;

	Renderer* Rend;
	Objects Obj;
	Fourier fourier;
	Vector2f SettingsPosition = DefaultSettingsPosition;
	Vector2i WindowPosition = Vector2i(0, 0);

	bool SettingsOpen = false;
	bool ObjectDescription = false;
	bool SomethingHasChanged = true;

public:
	void MainLoop();
	void CreateObjects();
	void Reset();

	void EventCheck(RenderWindow& window);
	void settingsEventCheck();
	void MouseEvents(Vector2f MousePosition);
	void PreEventModifiers();

	int CheckCollision(Vector2f mouse);
	float Distance2(Vector2f V0, Vector2f V1);
	void AddFunctionS0();
	bool isMouseInSquare(float x0, float x1, float y0, float y1);
	void WindowMovement(Vector2i NewWindowPosition);
	void change();
	
	void ButtonsState();
	void ButtonsActions();
	bool ButtonPressed(int i);
};
