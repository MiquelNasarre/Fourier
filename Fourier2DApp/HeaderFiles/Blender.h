#pragma once

#include "Header.h"
#include "Objects.h"
#include "Button.h"
#include "Selector.h"
#include "Popup.h"
#include "TickBox.h"
#include "Fourier.h"
#include "TimeFourier.h"

#define DefaultBlenderPos	Vector2f(1145.f,5.f)
#define MainSelectorPos		IncreaseVector(MenuPos, 5.f, 32.f)
#define AddBlenderButtonPos	IncreaseVector(MenuPos, 132.f, 34.f)

class Blender {
private:

	Sprite					Menu;
	std::vector<Texture>	MenuTextures;
	Button 					MenuButton;
	Vector2f				MenuPos;
	bool					OpenMenu;
	
	Selector				MainSelector;
	Button					AddBlenderButton;
	std::vector<TimeFourier>TimeFouriers;

	std::vector<Button>		ButtonScroller;
	Button					BigAddButton;


	void MenuMovements(int& change, int fourier);
	void MoveBlender(float dx, float dy);
	void NewBlender();

public:
	Blender();

	void Open();
	void Close();

	int EventCheck(Vector2i MousePos, std::vector<Fourier>& fouriers);

	void Render(Renderer& renderer);
	void Render(RenderWindow& window);
};
