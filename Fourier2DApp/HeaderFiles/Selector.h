#pragma once

#include "Header.h"
#include "Renderer.h"
#include "Popup.h"
#include "Objects.h"

class Selector {
private:
	Vector2f Position;
	Vector2i DimMain, DimOption;
	Font font;

	std::vector<Text> OptionTexts;
	std::vector<Texture> TexMain, TexOption, TexCloser;

	Sprite Main, Closer;
	std::vector<Sprite> OptionSprites;

	bool Pressing = false;
	bool IsOpen = false;
	bool ToBe;
	int CurrentSelection = -1;

	bool isOnOption(int N, Vector2i MousePos);
	void SetToPosition();

public:
	Selector(std::string TextureFile, std::vector<Vector2i> PosInFile, std::vector<Vector2i> SizeInFile, Vector2f position = Vector2f(0.f, 0.f), bool Draw = true);

	std::string getString(int N);
	int getSize();

	void SetVisibility(bool isOpen);
	void SetCurrentSelected(int N);
	void ChangeOpen();
	void setPosition(Vector2f Pos);
	void IncreasePosition(float dx, float dy);
	void ChangeName(std::string name);
	
	void AddOption(Text text);
	void AddOption(std::string String);
	void RemoveAll();
	void RemoveOption();
	void RemoveOption(int N);
	
	int EventCheck(Vector2i MousePos);
	void Render(Renderer& renderer);
	void Render(RenderWindow& window);
};