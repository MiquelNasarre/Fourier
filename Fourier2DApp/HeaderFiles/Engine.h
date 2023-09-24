#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"
#include "2dFourier.h"

#define InitialPoints 50
#define PointsColor RGBA('g')
#define PointsRadius 4.f
#define PointsFunction 200
#define StdKeyCooldown 8

class Engine {
private:
	int KeyCooldown = 0;
	int Dragging;
	Objects Obj;
	Renderer* Rend;
	bool SettingsOpen = false;
	int FourierDepth = 10;
	Vector2f SettingsPosition = Vector2f(-120.f, 5.f);

public:
	void MainLoop();
	void CreateObjects();

	void EventCheck(RenderWindow& window);
	int CheckCollision(Vector2f mouse);
	float Distance2(Vector2f V0, Vector2f V1);
	void AddFunctionS0();
	bool isMouseInSquare(float x0, float x1, float y0, float y1, Vector2f ScreenPos);
};
