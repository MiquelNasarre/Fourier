#include "Selector.h"

bool Selector::isOnOption(int N, Vector2i MousePos)
{
	if (MousePos.x >= Position.x && MousePos.x < Position.x + DimOption.x && MousePos.y >= Position.y + DimMain.y + DimOption.y * N && MousePos.y < Position.y + DimMain.y + DimOption.y * (N + 1))
		return true;
	return false;
}

Selector::Selector(std::string TextureFile, std::vector<Vector2i> PosInFile, std::vector<Vector2i> SizeInFile, Vector2f position, bool Draw) {
	ToBe = Draw;
	Position = position;
	DimMain = SizeInFile[0];
	DimOption = SizeInFile[1];

	Image image;
	Texture texture;
	image.loadFromFile(TextureFile);
	texture.loadFromImage(image, IntRect(PosInFile[0], SizeInFile[0]));
	TexMain.push_back(texture);
	texture.loadFromImage(image, IntRect(PosInFile[1], SizeInFile[0]));
	TexMain.push_back(texture);
	texture.loadFromImage(image, IntRect(PosInFile[2], SizeInFile[0]));
	TexMain.push_back(texture);
	texture.loadFromImage(image, IntRect(PosInFile[3], SizeInFile[0]));
	TexMain.push_back(texture);
	texture.loadFromImage(image, IntRect(PosInFile[4], SizeInFile[0]));
	TexMain.push_back(texture);
	texture.loadFromImage(image, IntRect(PosInFile[5], SizeInFile[0]));
	TexMain.push_back(texture);
	texture.loadFromImage(image, IntRect(PosInFile[5], SizeInFile[0]));
	TexMain.push_back(texture);
	texture.loadFromImage(image, IntRect(PosInFile[6], SizeInFile[1]));
	TexOption.push_back(texture);
	texture.loadFromImage(image, IntRect(PosInFile[7], SizeInFile[1]));
	TexOption.push_back(texture);
	texture.loadFromImage(image, IntRect(PosInFile[8], SizeInFile[2]));
	TexCloser.push_back(texture);
	Main.setTexture(TexMain[0]);
	Main.setPosition(Position);
	Option.setTexture(TexOption[0]);
	Closer.setTexture(TexCloser[0]);
	font.loadFromFile("Resources/Fonts/arial.ttf");
}

void Selector::IncreasePosition(float dx, float dy)
{
	Position = Vector2f(Position.x + dx, Position.y + dy);
	Main.setPosition(Position);
}

void Selector::SetVisibility(bool isOpen)
{
	ToBe = isOpen;
}

int Selector::SelectorEvents(Vector2i MousePos) {
	if (Pressing && Mouse::isButtonPressed(Mouse::Left))
		return -2;
	else
		Pressing = false;
	int event = -2;
	if (MousePos.x >= Position.x && MousePos.x < Position.x + DimMain.x && MousePos.y >= Position.y && MousePos.y < Position.y + DimMain.y) {
		event = -1;
		if (MousePos.x > Position.x + 109.f && MousePos.y > Position.y && Mouse::isButtonPressed(Mouse::Left)) {
			if (State < -1) {
				Main.setTexture(TexMain[5]);
				State = -1;
			}
			else {
				Main.setTexture(TexMain[2]);
				State = -2;
			}
		}
		else {
			if (State < -1) {
				Main.setTexture(TexMain[1]);
			}
			else {
				Main.setTexture(TexMain[4]);
			}
		}
	}
	else {
		if (State < -1) {
			Main.setTexture(TexMain[0]);
		}
		else {
			Main.setTexture(TexMain[3]);
		}
	}
	if (Mouse::isButtonPressed(Mouse::Left))
		Pressing = true;

	if (State >= -1) {
		for (int i = 0; i < (int)OptionTexts.size(); i++) {
			if (isOnOption(i, MousePos)) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					CurrentSelection = i;
					State = -2;
					return i;
				}
				else {
					State = i;
					return -1;
				}
			}
		}
		State = -1;
	}



	return event;
}

void Selector::AddOption(Text text)
{
	OptionTexts.push_back(text);
	CurrentSelection = OptionTexts.size() - 1;
}

void Selector::AddOption(std::string String)
{
	Text text;
	text.setString(String);
	text.setFont(font);
	text.setFillColor(Color(0,0,0,255));
	text.setCharacterSize(12);
	OptionTexts.push_back(text);
	CurrentSelection = OptionTexts.size() - 1;
}

void Selector::RemoveAll()
{
	CurrentSelection = -1;
	OptionTexts.clear();
}

void Selector::RemoveOption()
{
	OptionTexts.erase(OptionTexts.begin() + CurrentSelection);
	CurrentSelection--;
	if (CurrentSelection == -1 && OptionTexts.size())
		CurrentSelection++;
}

void Selector::RemoveOption(int N)
{
	OptionTexts.erase(OptionTexts.begin() + N);
	CurrentSelection--;
	if (CurrentSelection == -1 && OptionTexts.size())
		CurrentSelection++;
}

void Selector::RemoveOption(Text text)
{
	for (int i = 0; i < (int)OptionTexts.size(); i++) {
		if (OptionTexts[i].getString() == text.getString()) {
			OptionTexts.erase(OptionTexts.begin() + i);
		}
	}
	CurrentSelection--;
	if (CurrentSelection == -1 && OptionTexts.size())
		CurrentSelection++;
}

void Selector::RemoveOption(std::string String)
{
	for (int i = 0; i < (int)OptionTexts.size(); i++) {
		if (OptionTexts[i].getString() == String) {
			OptionTexts.erase(OptionTexts.begin() + i);
		}
	}
	CurrentSelection--;
	if (CurrentSelection == -1 && OptionTexts.size())
		CurrentSelection++;
}

void Selector::SetCurrentSelected(int N)
{
	CurrentSelection = N;
}

void Selector::SetOptionName(std::string name)
{
	OptionTexts[CurrentSelection].setString(name);
}

std::string Selector::getString(int N)
{
	return OptionTexts[N].getString();
}

void Selector::Render(Renderer& renderer)
{
	renderer.RenderSprite(Main);
	if (OptionTexts.size()) {
		OptionTexts[CurrentSelection].setPosition(Position.x + 6.f, Position.y + 4.f);
		renderer.RenderText(OptionTexts[CurrentSelection]);
	}
	if (State < -1)
		return;
	for (int i = 0; i < (int)OptionTexts.size(); i++) {
		Option.setPosition(Position.x, Position.y + DimMain.y + DimOption.y * i);
		if (State == i)
			Option.setTexture(TexOption[1]);
		else
			Option.setTexture(TexOption[0]);
		renderer.RenderSprite(Option);
		OptionTexts[i].setPosition(Option.getPosition().x + 4.f, Option.getPosition().y + 2.f);
	}
	renderer.RenderTexts(OptionTexts);
	Closer.setPosition(Position.x, Position.y + DimMain.y + DimOption.y * OptionTexts.size());
	renderer.RenderSprite(Closer);
}
