#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"

class Button {
private:

	Vector2f Position;
	Vector2f Dimensions;
	std::vector<Texture> Textures;
	Sprite sprite;
	Vector2f Scale;
	int State = 0;
	bool Visibility;
	Text text;
	Vector2f textPos;
	Font textFont;

public:
	Button(std::string TextureFile, std::vector<Vector2i> PosInFile, Vector2i SizeInFile, Vector2f scale, Vector2f position = Vector2f(0.f, 0.f), bool Draw = true, std::string textStr = "", Vector2f textPosition = Vector2f(0.f, 0.f), Font font = Font(), int characterSize = 14, Color FillColor = Color::Black);

	Vector2f GetPosition();
	Vector2f GetDimensions();
	int GetState();
	bool GetVisibility();

	void setPosition(Vector2f Pos);
	void setPosition(float x, float y);
	void setVisibility(bool V);

	void IncreasePosition(Vector2f Diff);
	void IncreasePosition(float dx, float dy);
	int ButtonEvents(Vector2i MouseScPos);

	void Render(Renderer& renderer);
	void Render(RenderWindow& window);
};
