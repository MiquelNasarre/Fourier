#pragma once

#include "Header.h"
#include "Button.h"
#include "Fourier.h"
#include "Renderer.h"

class ToolBox {
private:
	Button		IconButton;

public:
	ToolBox();

	bool EventCheck(Vector2i MousePos, std::vector<Fourier> fouriers);
	void Render(Renderer& renderer);
};
