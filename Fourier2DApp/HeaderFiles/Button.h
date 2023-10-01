#pragma once

#include "Header.h"
#include "Objects.h"
#include "Renderer.h"

class Button {
private:

	Font					textFont;
	Text					text;
	std::vector<Texture>	Textures;
	Sprite					sprite;

	Vector2f				Position;
	Vector2f				Dimensions;
	Vector2f				textPos;
	Vector2f				Scale;

	int						State = 0;
	bool					Visibility;

public:
	static const int Pressed	=  3;
	static const int Pressing	= -3;
	static const int Hovered	=  2;
	static const int Hovering	= -2;
	static const int Unhovered	=  1;
	static const int NoState	= -1;

	Button() {}
	Button(std::string TextureFile, std::vector<Vector2i> PosInFile, Vector2i SizeInFile, Vector2f scale, Vector2f position = Vector2f(0.f, 0.f), bool Draw = true, std::string textStr = "", Vector2f textPosition = Vector2f(0.f, 0.f), Font font = Font(), int characterSize = 14, Color FillColor = Color::Black);
	Button(const Button& other);

	Vector2f GetPosition();
	Vector2f GetDimensions();
	int GetState();
	bool GetVisibility();

	void setPosition(Vector2f Pos);
	void setPosition(float x, float y);
	void IncreasePosition(Vector2f Diff);
	void IncreasePosition(float dx, float dy);
	void setVisibility(bool V);
	void setTexture(int t);

	void setTextures(std::vector<Texture> textures);
	void setFont(Font font);
	void setString(std::string String);

	int EventCheck(Vector2i MouseScPos);
	void Render(Renderer& renderer);
	void Render(RenderWindow& window);
};
