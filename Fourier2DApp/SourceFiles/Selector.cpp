#include "Selector.h"

bool Selector::isOnOption(int N, Vector2i MousePos)
{
	if (InsideRectangle(MousePos, Vector2f(Position.x, Position.y + DimMain.y + DimOption.y * (N - SlidePos)), DimOption) && 
		InsideRectangle(MousePos, Vector2f(Position.x, Position.y + DimMain.y), Vector2i(DimOption.x, int(DimOption.y * MaxLength))))
		return true;
	return false;
}

void Selector::SetToPosition()
{
	for (int i = 0; i < (int)OptionSprites.size(); i++) {
		OptionSprites[i].setPosition(DefaultOptionPos(i));
		OptionTexts[i].setPosition(AddVectors(DefaultOptionPos(i), DefaultTextPos));
	}
	if ((float)OptionTexts.size() < MaxLength)
		Closer.setPosition(IncreaseVector(AddVectors(DefaultOptionPos(OptionTexts.size()), Position), 0, (float)DimMain.y));
	else
		Closer.setPosition(IncreaseVector(AddVectors(DefaultOptionPos(MaxLength), Position),0, (float)DimMain.y));
}

//	Public

Selector::Selector(std::string TextureFile, std::vector<Vector2i> PosInFile, std::vector<Vector2i> SizeInFile, Vector2f position, bool Draw) {
	ToBe = Draw;
	Position = position;
	DimMain = SizeInFile[0];
	DimOption = SizeInFile[1];
	CurrentSelection = -1;

	Image image;
	Texture texture;
	image.loadFromFile(TextureFile);
	TransparentGreenScreen(&image);
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
	Closer.setTexture(TexCloser[0]);
	font.loadFromFile("Resources/Fonts/arial.ttf");
}

Selector::Selector(const Selector& other)
{
	Position = other.Position;
	DimMain = other.DimMain;
	DimOption = other.DimOption;
	font = other.font;

	OptionTexts = other.OptionTexts;
	TexMain = other.TexMain;
	TexOption = other.TexOption;
	TexCloser = other.TexCloser;

	Main = other.Main;
	Closer = other.Closer;
	Closer.setTexture(TexCloser[0]);
	OptionSprites = other.OptionSprites;

	Pressing = false;
	ToBe = other.ToBe;
	CurrentSelection = other.CurrentSelection;
	WhenOpen = other.WhenOpen;
}

void Selector::IncreasePosition(float dx, float dy)
{
	Position = Vector2f(Position.x + dx, Position.y + dy);
	Main.setPosition(Position);
	SetToPosition();
}

void Selector::setVisibility(bool isOpen)
{
	ToBe = isOpen;
}

void Selector::pushBack(Text text)
{
	OptionTexts.push_back(text);
	OptionSprites.push_back(Sprite(TexOption[0]));
	CurrentSelection = OptionTexts.size() - 1;
	SetToPosition();
}

void Selector::pushBack(std::string String)
{
	Text text;
	text.setString(String);
	text.setFont(font);
	text.setFillColor(Color(0,0,0,255));
	text.setCharacterSize(12);
	OptionTexts.push_back(text);
	OptionSprites.push_back(Sprite(TexOption[0]));
	CurrentSelection = OptionTexts.size() - 1;
	SetToPosition();
}

void Selector::clear()
{
	CurrentSelection = -1;
	OptionTexts.clear();
	OptionSprites.clear();
}

void Selector::erase()
{
	OptionTexts.erase(OptionTexts.begin() + CurrentSelection);
	OptionSprites.erase(OptionSprites.begin() + CurrentSelection);
	CurrentSelection--;
	if (CurrentSelection == -1 && OptionTexts.size())
		CurrentSelection++;
	SetToPosition();
}

void Selector::erase(int N)
{
	OptionTexts.erase(OptionTexts.begin() + N);
	CurrentSelection--;
	if (CurrentSelection == -1 && OptionTexts.size())
		CurrentSelection++;
	SetToPosition();
}

void Selector::setCurrentSelected(int N)
{
	CurrentSelection = N;
}

void Selector::Open()
{
	Main.setTexture(TexMain[5]);
	IsOpen = true;
}

void Selector::Close()
{
	Main.setTexture(TexMain[2]);
	IsOpen = false;
}

void Selector::setName(std::string name)
{
	if (!name.size())
		return;
	OptionTexts[CurrentSelection].setString(name);
}

void Selector::WhenToOpen(int n)
{
	WhenOpen = n;
}

std::string Selector::getString(int N)
{
	return OptionTexts[N].getString();
}

int Selector::getSize()
{
	return OptionTexts.size();
}

int Selector::getCurrentSelected()
{
	return CurrentSelection;
}

void Selector::setPosition(Vector2f Pos)
{
	Position = Pos;
	Main.setPosition(Position);
	SetToPosition();
}

int Selector::EventCheck(Vector2i MousePos) {
	if (Pressing && Mouse::isButtonPressed(Mouse::Left))
		return -2;
	else
		Pressing = false;
	if (InsideRectangle(MousePos, Position, DimMain) && WhenOpen != OpenNever) {
		if (MousePos.x > Position.x + 91.f &&
			MousePos.x < Position.x + 105.f &&
			Mouse::isButtonPressed(Mouse::Left) &&
			IsOpen == false && CurrentSelection != -1)
			setName(Popup::InputString());
		if (MousePos.x > Position.x + 109.f && ((Mouse::isButtonPressed(Mouse::Left) && WhenOpen == OpenWhenPressed) || WhenOpen == OpenWhenHovered)) {
			if (IsOpen)
				Close();
			else
				Open();
		}
		else {
			if (IsOpen && SetTexture(Main, TexMain[4]))
				return -1;
			else if (!IsOpen && SetTexture(Main, TexMain[1]))
				return -1;
				
		}
	}
	else {
		if (IsOpen && SetTexture(Main, TexMain[3]))
			return -1;
		else if (!IsOpen && SetTexture(Main, TexMain[0]))
			return -1;
	}
	if (Mouse::isButtonPressed(Mouse::Left))
		Pressing = true;

	int change = -2;
	if (IsOpen) {

		if ((int)OptionTexts.size() > MaxLength) {
			if ((Keyboard::isKeyPressed(Keyboard::Down)) && SlidePos < OptionTexts.size() - MaxLength)
				SlidePos += 0.2f;
			if (Keyboard::isKeyPressed(Keyboard::Up) && SlidePos > 0)
				SlidePos -= 0.2f;
			if (SlidePos > OptionTexts.size() - MaxLength)
				SlidePos = OptionTexts.size() - MaxLength;
		}
		else
			SlidePos = 0.f;

		for (int i = 0; i < (int)OptionTexts.size(); i++) {
			if (isOnOption(i, MousePos)) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					CurrentSelection = i;
					IsOpen = false;
					return i;
				}
				else {
					OptionSprites[i].setTexture(TexOption[1]);
					for (int j = i + 1; j < (int)OptionSprites.size(); j++)
						SetTexture(OptionSprites[j], TexOption[0]);
					return -1;
				}
			}
			else if(SetTexture(OptionSprites[i],TexOption[0]))
				change = -1;
		}
	}
	return change;
}

void Selector::Render(Renderer& renderer)
{
	renderer.RenderSprite(Main);
	if (OptionTexts.size() && CurrentSelection != -1) {
		OptionTexts[CurrentSelection].setPosition(Position.x + 6.f, Position.y + 4.f);
		renderer.RenderText(OptionTexts[CurrentSelection]);
		OptionTexts[CurrentSelection].setPosition(AddVectors(DefaultOptionPos(CurrentSelection), DefaultTextPos));
	}
	if (!IsOpen || !OptionTexts.size())
		return;

	RenderTexture texture;
	texture.create(DimOption.x, DimOption.y * OptionTexts.size());
	texture.clear(Color::Transparent);
	for (int i = 0; i < (int)OptionTexts.size(); i++) {
		texture.draw(OptionSprites[i]);
		texture.draw(OptionTexts[i]);
	}
	texture.display();
	Sprite sprite;
	sprite.setTexture(texture.getTexture());
	sprite.setPosition(Position.x, Position.y + DimMain.y);
	if ((int)OptionTexts.size() > MaxLength)
		sprite.setTextureRect(IntRect(0, int(SlidePos * DimOption.y), DimOption.x, int(MaxLength * DimOption.y)));
	renderer.RenderSprite(sprite);
	renderer.RenderSprite(Closer);
}

void Selector::Render(RenderWindow& window)
{
	
}
