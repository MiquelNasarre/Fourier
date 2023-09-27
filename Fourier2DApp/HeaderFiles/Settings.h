#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"
#include "Selector.h"

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
	
	bool IsOpen;
	unsigned char buttonCooldown;

	void MovementEvents(int& Change, Vector2f &SidebarPos);
	void MouseEvents(int& Change, Vector2i& MouseScPos, bool& PressingButton);
	bool SettingsIcon(Vector2i& MouseScPos);

public:
	std::vector<Selector>   Selectors;

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


	Settings();
	void SetValues(std::vector<int> values);
	void DrawSettings(Renderer& renderer);
	int SettingsEvents(Vector2i MouseScPos, bool Occupied, bool& PressingButton);
	void DeleteSelected();
	void EmptySelector();
	void setSelector(int n);
	std::string getSelectorString(int N);
	void AddToSelector(std::string String);

};
