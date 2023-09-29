#pragma once

#include "Header.h"
#include "Renderer.h"

class TickBox {
private:
	Sprite Box;
	std::vector<Texture> TexBox;
	Vector2i Size;
	Vector2f Position;
	bool ticked;
	bool Pressing = false;
	bool Visibility;

public:
	TickBox(std::string Filename, Vector2i Pos0, Vector2i Pos1, Vector2i size, Vector2f position = Vector2f(0.f, 0.f), bool init = false, bool visible = true);

	bool switchBox();
	void setState(bool T);
	void setPosition(Vector2f pos);
	void increasePosition(Vector2f diff);
	void increasePosition(float dx, float dy);
	void setVisibility(bool T);

	int EventCheck(Vector2i MousePos);

	void Render(RenderWindow& window);
	void Render(Renderer& renderer);
	
};