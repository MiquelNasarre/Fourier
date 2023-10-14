#pragma once

#include "Header.h"
#include "Renderer.h"

#define DefaultNumberBarInitializer "Resources/Textures/CustomButtons.png",std::vector<Vector2i>({Vector2i(293,458),Vector2i(293,483),Vector2i(293,508)}),Vector2i(36,21)

class NumberBar {
private:
	Vector2f Position;
	Vector2i Dimensions;
	int Number;
	std::string StrNumber;
	Font font;
	Text TextNumber;
	Sprite Holder;
	std::vector<Texture> TexHolder;
	int Maximum;
	int Minimum;
	bool Pressed = false;
	bool JustPressed = false;

public:
	NumberBar(std::string Filename, std::vector<Vector2i> TextureLocations, Vector2i Size, Vector2f position, int Max, int Minimum, int Initial = 0, Font InitialFont = Font());

	void setNumber(int number);
	void setFont(Font f);
	void setMaximum(int Max);
	void setPosition(Vector2f Position);

	int getNumber();
	Sprite getSprite();

	int EventCheck(Event& event, Vector2i MousePos);

	void Render(Renderer& renderer);
	void Render(RenderWindow& window);
};