#include "TickBox.h"

TickBox::TickBox(std::string Filename, Vector2i Pos0, Vector2i Pos1, Vector2i size, Vector2f position, bool init, bool visible)
	:Size{ size }, Position{ position }, ticked{ init }, Visibility{ visible }
{
	Image image;
	image.loadFromFile(Filename);
	TransparentGreenScreen(&image);
	Texture texture;
	texture.loadFromImage(image, IntRect(Pos0, size));
	TexBox.push_back(texture);
	texture.loadFromImage(image, IntRect(Pos1, size));
	TexBox.push_back(texture);
	Box.setPosition(position);
	Box.setTexture(TexBox[ticked]);
}

void TickBox::setState(bool T)
{
	ticked = T;
	SetTexture(Box, TexBox[T]);
}

bool TickBox::switchBox()
{
	if (ticked)
		ticked = false;
	else
		ticked = true;
	Box.setTexture(TexBox[ticked]);
	Pressing = true;
	return ticked;
}

void TickBox::setPosition(Vector2f pos)
{
	Position = pos;
	Box.setPosition(Position);
}

void TickBox::increasePosition(Vector2f diff)
{
	Position = Vector2f(Position.x + diff.x, Position.y + diff.y);
	Box.setPosition(Position);
}

void TickBox::increasePosition(float dx, float dy)
{
	Position = Vector2f(Position.x + dx, Position.y + dy);
	Box.setPosition(Position);
}

void TickBox::setVisibility(bool T)
{
	Visibility = T;
}

int TickBox::EventCheck(Vector2i MousePos)
{
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (InsideRectangle(MousePos, Position, Size) && !Pressing)
			return (int)switchBox() + 1;
		Pressing = true;
	}
	else 
		Pressing = false;
	return 0;
}

void TickBox::Render(RenderWindow& window)
{
	if (Visibility)
		window.draw(Box);
}

void TickBox::Render(Renderer& renderer)
{
	if (Visibility)
		renderer.RenderSprite(Box);
}