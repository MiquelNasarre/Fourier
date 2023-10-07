#pragma once

#include "Header.h"
#include "Button.h"
#include "Fourier.h"
#include "Renderer.h"

#define DefaultToolBoxPos	Vector2f(10.f,605.f)
#define MovementSpeed		0.01f
#define ExpansionRate		1.03f
#define ShrinkingRate		0.97f
#define RotatingRate		0.015f

class ToolBox {
private:
	Button		IconButton;
	Texture		TexBox;
	Sprite		Box;

	std::vector<Button> Tools;
	
	Vector2f Position = IncreaseVector(DefaultToolBoxPos, 0.f, 110.f);
	bool isOpen = false;
	

	static const int MoveUp			= 0;
	static const int MoveDown		= 1;
	static const int MoveLeft		= 2;
	static const int MoveRight		= 3;
	static const int Center			= 4;
	static const int RotateRight	= 5;
	static const int RotateLeft		= 6;
	static const int FlipHorizontal	= 7;
	static const int FlipVertical	= 8;
	static const int Expand			= 9;
	static const int Shrink			=10;
	static const int SquishHort		=11;
	static const int SquishVert		=12;
	static const int EnlargeHort	=13;
	static const int EnlargeVert	=14;
	

public:
	ToolBox();

	static Vector2f centerFourier(Fourier& fourier);
	static void		moveFourier(Fourier& fourier, Vector2f dV);
	static void		moveToCenter(Fourier& fourier);
	static void		ExpandFourier(Fourier& fourier, float k);
	static void		RotateFourier(Fourier& fourier, double theta);
	static void		ExpHortFourier(Fourier& fourier, float k);
	static void		ExpVertFourier(Fourier& fourier, float k);

	bool Close();
	bool EventCheck(Vector2i MousePos, Fourier& fourier, bool& saves, int number);
	void Render(Renderer& renderer);
};
