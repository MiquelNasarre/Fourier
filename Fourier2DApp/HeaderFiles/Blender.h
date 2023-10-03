#pragma once

#include "Header.h"
#include "Objects.h"
#include "Button.h"
#include "Selector.h"
#include "Popup.h"
#include "TickBox.h"
#include "Fourier.h"
#include "TimeFourier.h"
#include "Scroller.h"

#define DefaultBlenderPos	Vector2f(1145.f,5.f)
#define MainSelectorPos		IncreaseVector(MenuPos, 5.f, 32.f)
#define AddBlenderButtonPos	IncreaseVector(MenuPos, 132.f, 34.f)
#define ScrollerBlenderPos	IncreaseVector(MenuPos, 15.f, 127.f)
#define PlayButtonPos		IncreaseVector(MenuPos, 55.f, 282.f)
#define BackButtonPos		IncreaseVector(MenuPos, 27.f, 282.f)
#define ForwardButtonPos	IncreaseVector(MenuPos,101.f, 282.f)
#define IncreaseButtonPos	IncreaseVector(MenuPos,  5.f, 283.f)
#define DecreaseButtonPos	IncreaseVector(MenuPos,129.f, 283.f)
#define HideAllButtonPos	IncreaseVector(MenuPos,  7.f, 217.f)
#define ShowAllButtonPos	IncreaseVector(MenuPos, 82.f, 217.f)
#define ResetButtonPos		IncreaseVector(MenuPos,  7.f, 245.f)
#define DeleteButtonPos		IncreaseVector(MenuPos, 82.f, 245.f)

class Blender {
private:

	Sprite					Menu;
	std::vector<Texture>	MenuTextures;
	Button 					MenuButton;
	Vector2f				MenuPos;
	bool					OpenMenu;
	bool					TimePlaying;
	bool					Pressing;
	
	int						currentBlender;
	Selector				MainSelector;
	Button					AddBlenderButton;
	std::vector<TimeFourier>TimeFouriers;
	std::vector<Scroller>	scrollers;

	Button					PlayButton;
	Button					StopButton;
	Button					GoBack;
	Button					GoForward;
	Button					Increase;
	Button					Decrease;


	Button					HideAll;
	Button					ShowAll;
	Button					Reset;
	Button					Delete;

	void MenuMovements(int& change, int fourier);
	void MoveBlender(float dx, float dy);
	void NewBlender();

public:
	static const int Hide = 2;
	static const int Show = 3;

	Blender();

	void Open();
	void Close();

	int EventCheck(Vector2i MousePos, std::vector<Fourier>& fouriers);

	void Render(Renderer& renderer);
	void Render(RenderWindow& window);
};
