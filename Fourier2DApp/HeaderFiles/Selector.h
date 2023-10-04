#pragma once

#include "Header.h"
#include "Renderer.h"
#include "Popup.h"
#include "Objects.h"

#define DefaultTextPos		Vector2f(4.f, 2.f)
#define DefaultOptionPos(x) Vector2f(0.f, DimOption.y * x)

class Selector {
public:
	static const int OpenWhenPressed = 0;
	static const int OpenWhenHovered = 1;
	static const int OpenNever		 = 2;

private:
	Vector2f Position;
	Vector2i DimMain, DimOption;
	Font font;

	std::vector<Text>		OptionTexts;
	std::vector<Texture>	TexMain, TexOption, TexCloser;
	Sprite					Main, Closer;
	std::vector<Sprite>		OptionSprites;

	bool Pressing = false;
	bool ToBe;
	int CurrentSelection;
	int WhenOpen = OpenWhenPressed;

	float MaxLength = 8.f;
	float SlidePos = 0.f;

	bool isOnOption(int N, Vector2i MousePos);
	void SetToPosition();

public:
	bool IsOpen = false;
	Selector(std::string TextureFile, std::vector<Vector2i> PosInFile, std::vector<Vector2i> SizeInFile, Vector2f position = Vector2f(0.f, 0.f), bool Draw = true);
	Selector(const Selector& other);

	std::string	getString(int N);
	int			getSize();
	int			getCurrentSelected();

	void setVisibility(bool isOpen);
	void setCurrentSelected(int N);
	void setName(std::string name);
	void setPosition(Vector2f Pos);
	void IncreasePosition(float dx, float dy);

	void WhenToOpen(int n);
	void Open();
	void Close();
	
	void pushBack(Text text);
	void pushBack(std::string String);
	void clear();
	void erase();
	void erase(int N);
	
	int EventCheck(Vector2i MousePos);
	void Render(Renderer& renderer);
	void Render(RenderWindow& window);
};