#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"
#include "Fourier.h"
#include "Settings.h"
#include "Popup.h"

#define StdKeyCooldown 8
#define StdButtonCooldown 4
#define DefaultInitialPoints 40
#define DefaultPointsFunction 500
#define DefaultFourierDepth 15
#define InitialRadius  1 + ((float)TotalFouriersHad - 1) / 6

class Engine {
private:
	std::vector<int> Values;
	int KeyCooldown = 0;
	int currentFourier = 0;
	int TotalFouriersHad = 0;

	Renderer* Rend;
	std::vector<Fourier> fourier;
	Settings settings;

	Vector2f SettingsPosition = DefaultSettingsPosition;
	Vector2i WindowPosition = Vector2i(0, 0);

	bool SettingsOpen = false;
	bool SomethingHasChanged = true;
	bool PressingButton = false;

	Color ColorWheel(int n);
public:
	Engine();

	void MainLoop();
	void Reset();
	void AddFourier();
	void DeleteFourier();

	void EventCheck(RenderWindow& window);
	void KeyboardEventCheck();

	Vector2i MouseWindowPosition();
	void WindowMovement(Vector2i NewWindowPosition);
	void change();
	bool fouriersOccupied();
	void SetFourier(int N);
	void LoadFromFile(std::string filename);
	void SaveToFile(std::string filename);
	
	void ButtonsActions(int ButtonPressed);
	
};
