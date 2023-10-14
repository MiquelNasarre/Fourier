#pragma once

#include "Header.h"
#include "Button.h"
#include "DecimalBar.h"

class Settings {
public:
	static const unsigned int DiscreteErrorText = 3;
	static const unsigned int CoefficientsText  = 5;

	Button Play;
	Button Pause;
	Button IncreaseSpeed;
	Button DecreaseSpeed;
	Button DataWindow;
	Button Draw;
	Button Save;
	Button Load;
	Button Show;
	Button Hide;
	DecimalBar ErrorBar;
	DecimalBar NumberPoints;

	std::vector<Text> texts;

	Texture TexHoder;
	Sprite Holder;

	bool playing = true;
	float error = 0.05f;
	int points = 200;
	Font font;
	bool pointsVisible = false;

	Settings();

	void render(RenderWindow& window);
};