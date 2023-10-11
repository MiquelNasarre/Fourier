#pragma once

#include "Header.h"
#include "Button.h"
#include "NumberBar.h"

class Settings {
public:
	Button Play;
	Button Pause;
	Button DataWindow;
	NumberBar ErrorBar;

	bool playing = true;
	float error = 0.02f;
	
	Settings();

	void render(RenderWindow& window);
};