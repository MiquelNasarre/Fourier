#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"
#include "Selector.h"
#include "Button.h"
#include "TickBox.h"

#define DefaultSettingsPosition Vector2f(-120.f, 5.f)
#define SlideVelocity 10.f
#define DefaultButtonCooldown 6
#define OpenedTexture 0
#define ClosedTexture 1
#define FourierPoints	0
#define PointsFunction	1
#define FourierDepth	2

class Settings {
private:

	Sprite Sidebar;
	std::vector<Texture>	Textures;
	std::vector<Button>		Buttons;
	std::vector<Font>		Fonts;
	std::vector<Text>		Texts;
	std::vector<int>		Values;
	std::vector<TickBox>	Boxes;

	bool IsOpen;
	unsigned char buttonCooldown;
	bool Freeze = false;

	void MovementEvents(int& Change);
	void MouseEvents(int& Change, Vector2i& MousePos, bool& PressingButton);

public:
	Selector selector;

	static const int IncreaseDepth      = 2;
	static const int DecreaseDepth      = 3;
	static const int IncreaseSmoothness	= 4;
	static const int DecreaseSmoothness = 5;
	static const int IncreasePoints     = 6;
	static const int DecreasePoints     = 7;
	static const int Reset				= 8;
	static const int Draw				= 9;
	static const int New				=10;
	static const int Delete				=11;
	static const int Load				=12;
	static const int Save				=13;
	static const int ColorSelector		=14;
	static const int HidePoints			=15;
	static const int ShowPoints			=16;
	static const int HideFunction		=17;
	static const int ShowFunction		=18;
	static const int HideGrid			=19;
	static const int ShowGrid			=20;

	Settings();

	void setValues(std::vector<int> &values);
	void setPointsVisibility(bool T);
	void setFunctionVisibility(bool T);
	void close();
	void open();

	int EventCheck(Vector2i MousePos, bool Occupied, bool& PressingButton);
	void Render(Renderer& renderer);
};
