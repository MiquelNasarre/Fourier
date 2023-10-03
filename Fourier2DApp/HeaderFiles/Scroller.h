#pragma once

#include "Header.h"
#include "Button.h"
#include "Selector.h"
#include "Objects.h"
#include "Renderer.h"

#define AddDownPos		IncreaseVector(Position,43.f,22.f)
#define AddUpPos		IncreaseVector(Position,43.f,-10.f)
#define DeletePos		IncreaseVector(Position,107.f,6.f)

class Scroller {
private:
	Font				font;
	Vector2f			Position;
	Button				BigAddButton;
	Button				AddDown;
	Button				AddUp;
	Button				Delete;
	std::vector<Button> Selections;
	float				ScrollerPos;
	int					CurrentSelected = -1;
	bool				pressing;
	Selector			ScrollerSelector;

	std::vector<void*>	Tracker;

	Vector2f calculatePos(int n);
	

public:

	Scroller(Vector2f position = Vector2f());
	Scroller(const Scroller& other);

	void setPosition(Vector2f position);

	bool TrackerUpdate(std::vector<void*> OptionsPointer, std::vector<void*>& track);
	void EventCheck(Vector2i MousePos, std::vector<std::string> Options, std::vector<void*> OptionsPointer, std::vector<void*>& track);
	void Render(Renderer& renderer);
};
