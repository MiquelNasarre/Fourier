#pragma once

#include "Header.h"

#define DefaultDecimalBarInitializer "Resources/Textures/CustomButtons.png",std::vector<Vector2i>({Vector2i(293,458),Vector2i(293,483),Vector2i(293,508)}),Vector2i(36,21)

class DecimalBar {
private:
	Vector2f Position;
	Vector2i Dimensions;
	float Number;
	std::string StrNumber;
	Font font;
	Text TextNumber;
	Sprite Holder;
	std::vector<Texture> TexHolder;
	bool Pressed = false;
	bool JustPressed = false;
	int MaxDecimals;
	int MaxIntegers;
	int MaxFigures;

	int integerSize = 0;
	bool decimal = false;
	int decimalSize = 0;

public:
	DecimalBar(std::string Filename, std::vector<Vector2i> TextureLocations, Vector2i Size, Vector2f Scale, Vector2f position, float Initial = 0, Font InitialFont = Font(), int maxDecimals = 6, int maxIntegers = 4, int maxFigures = 6);

	void setNumber(float number);
	void setFont(Font f);
	void setPosition(Vector2f Position);

	float getNumber();
	Sprite getSprite();

	void setNumberFromString();
	void updateText();
	int EventCheck(Event& event, Vector2i MousePos);

	void Render(RenderWindow& window);
};