#pragma once

#include "Header.h"
#include "Renderer.h"
#include "Popup.h"
#include "Objects.h"

class Selector {
public:
	static const int OpenWhenPressed = 0;
	static const int OpenWhenHovered = 1;
	static const int OpenNever		 = 2;

private:
	Vector2f Position;
	Vector2i DimMain, DimOption;
	Font font;

	std::vector<Text> OptionTexts;
	std::vector<Texture> TexMain, TexOption, TexCloser;

	Sprite Main, Closer;
	std::vector<Sprite> OptionSprites;

	bool Pressing = false;
	bool ToBe;
	int CurrentSelection;
	int WhenOpen = OpenWhenPressed;

	bool isOnOption(int N, Vector2i MousePos);
	void SetToPosition();

public:
	bool IsOpen = false;
	Selector(std::string TextureFile, std::vector<Vector2i> PosInFile, std::vector<Vector2i> SizeInFile, Vector2f position = Vector2f(0.f, 0.f), bool Draw = true);

	std::string getString(int N);
	int getSize();
	int getCurrentSelected();

	void SetVisibility(bool isOpen);
	void SetCurrentSelected(int N);
	void Open();
	void Close();
	void setPosition(Vector2f Pos);
	void IncreasePosition(float dx, float dy);
	void ChangeName(std::string name);
	void WhenToOpen(int n);
	
	void AddOption(Text text);
	void AddOption(std::string String);
	void RemoveAll();
	void RemoveOption();
	void RemoveOption(int N);
	
	int EventCheck(Vector2i MousePos);
	void Render(Renderer& renderer);
	void Render(RenderWindow& window);
};