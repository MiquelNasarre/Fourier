#pragma once

#include "Header.h"
#include "Renderer.h"

class Selector {
private:
	Vector2f Position;
	Vector2i DimMain, DimOption;
	Font font;

	std::vector<Text> OptionTexts;
	std::vector<Texture> TexMain, TexOption, TexCloser;

	Sprite Main, Option, Closer;

	bool Pressing = false;
	int State = -2;
	bool ToBe;
	int CurrentSelection = -1;

	bool isOnOption(int N, Vector2i MousePos);

public:
	Selector(std::string TextureFile, std::vector<Vector2i> PosInFile, std::vector<Vector2i> SizeInFile, Vector2f position = Vector2f(0.f, 0.f), bool Draw = true);
	void SetVisibility(bool isOpen);
	void IncreasePosition(float dx, float dy);
	int SelectorEvents(Vector2i MousePos);
	void AddOption(Text text);
	void AddOption(std::string String);
	void RemoveAll();
	void RemoveOption();
	void RemoveOption(int N);
	void RemoveOption(Text text);
	void RemoveOption(std::string String);
	void SetCurrentSelected(int N);
	void SetOptionName(std::string name);
	std::string getString(int N);

	void Render(Renderer &renderer);
};