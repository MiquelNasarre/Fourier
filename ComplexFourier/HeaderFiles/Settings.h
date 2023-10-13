#pragma once

#include "Header.h"
#include "Button.h"
#include "DecimalBar.h"

class Settings {
public:
	Button Play;
	Button Pause;
	Button IncreaseSpeed;
	Button DecreaseSpeed;
	Button DataWindow;
	Button Draw;
	DecimalBar ErrorBar;
	DecimalBar NumberPoints;

	std::vector<Text> texts;

	Texture TexHoder;
	Sprite Holder;

	bool playing = true;
	float error = 0.02f;
	int points = 200;
	Font font;

	Settings();

	void render(RenderWindow& window);
};