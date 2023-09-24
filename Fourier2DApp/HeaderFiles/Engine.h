#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"
#include "2dFourier.h"

#define InitialPoints 20
#define PointsColor RGBA('g')
#define PointsRadius 4.f
#define PointsFunction 200

class Engine {
private:
	int Dragging;
	Objects Obj;
public:
	void MainLoop();
	void CreateObjects();

	void EventCheck(RenderWindow& window);
	int CheckCollision(Vector2f mouse);
	float Distance2(Vector2f V0, Vector2f V1);
	void AddFunctionS0();
};
