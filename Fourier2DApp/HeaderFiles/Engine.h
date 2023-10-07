#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"
#include "Fourier.h"
#include "Settings.h"
#include "Popup.h"
#include "Blender.h"
#include "ToolBox.h"

#define StdKeyCooldown 8
#define StdButtonCooldown 4
#define DefaultInitialPoints 40
#define DefaultPointsFunction 500
#define DefaultFourierDepth 15
#define InitialRadius  1 + ((float)TotalFouriersHad - 1) / 6

class Engine {
private:
	RenderWindow window;
	Renderer renderer;

	std::vector<SaveState> saveStates;

	Settings settings;
	Blender blender;
	ToolBox toolBox;
	
	std::vector<Fourier> fourier;

	std::vector<int> Values;
	int KeyCooldown = 0;
	int currentFourier = 0;
	int TotalFouriersHad = 0;
	int currentState = -1;

	Vector2f SettingsPosition = DefaultSettingsPosition;
	Vector2i WindowPosition = Vector2i(0, 0);

	bool SettingsOpen	= false;
	bool Change			= true;
	bool PressingButton = false;
	bool ShowGrid		= true;

	Color ColorWheel(int n);

	void AddFourier();
	void DeleteFourier();
	void DuplicateFourier();

	Vector2i mousePosition();
	void WindowMovement(Vector2i NewWindowPosition);
	void change();
	bool fouriersOccupied();
	void LoadFromFile(std::string filename);
	void SaveToFile(std::string filename);
	
	void purgeStates();
	void pushState(int Nature);
	void pushState(int nature, int identifier);
	void pushState(int nature, int identifier, std::vector<Point> points, Color color, std::vector<int> values, std::string name);
	void loadPrev();
	void loadNext();

	void EventCheck(RenderWindow& window);
	void ButtonsActions(int ButtonPressed);

	void Display(RenderWindow& window);

public:
	Engine();
	void MainLoop();
};
