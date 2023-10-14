#pragma once

#include "Header.h"
#include "Button.h"
#include "NumberBar.h"
#include "Renderer.h"

#define MaxNameSize 14

class Popup {
private:
	static Image createColorPalete(Vector2i size = Vector2i(256,256));
	static Color PixelColor(int x, int y, int width, int height);
	static Vector2i MousePosition(Window& window);
	static void BrightnessSliderImage(Image& image, Vector2i currentSelected);
	static Vector3i InversePixelColor(Color current, int width, int height);
public:
	static std::string InputString(std::string WindowName = "Set a name", int MaxSize = MaxNameSize);
	static Color ColorSelection(Color Current = Color::Red);
};