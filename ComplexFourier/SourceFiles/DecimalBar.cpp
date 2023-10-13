#include "DecimalBar.h"

DecimalBar::DecimalBar(std::string Filename, std::vector<Vector2i> TextureLocations, Vector2i Size, Vector2f Scale, Vector2f position, float Initial, Font InitialFont, int maxDecimals, int maxIntegers, int maxFigures)
	:font{ InitialFont }, Position{ position }, Dimensions{ (Vector2f)Size * Scale }, MaxDecimals{ maxDecimals }, MaxIntegers{ maxIntegers }, MaxFigures{ maxFigures }
{
	Image image;
	image.loadFromFile(Filename);
	TransparentGreenScreen(&image);
	Texture texture;
	texture.loadFromImage(image, IntRect(TextureLocations[0], Size));
	TexHolder.push_back(texture);
	texture.loadFromImage(image, IntRect(TextureLocations[1], Size));
	TexHolder.push_back(texture);
	texture.loadFromImage(image, IntRect(TextureLocations[2], Size));
	TexHolder.push_back(texture);
	Holder.setTexture(TexHolder[0]);
	Holder.setPosition(Position);
	Holder.setScale(Scale);
	TextNumber.setCharacterSize(14);
	TextNumber.setFillColor(Color::Black);
	TextNumber.setFont(font);
	setNumber(Initial);
}

void DecimalBar::setNumber(float number)
{
	Number = number;
	int intNum = int(number);
	StrNumber = std::to_string(intNum);
	if (intNum)
		integerSize = int(log10(intNum) + 1);
	else
		integerSize = 0;
	if (!MaxDecimals)
		return updateText();

	StrNumber.push_back('.');
	float decNum = Number;
	for (int i = 0; i < MaxDecimals; i++) {
		decNum -= (int)decNum;
		decNum *= 10;
		StrNumber.push_back(int(decNum) + 48);
		decimalSize++;
	}
	decimal = true;
	bool nines = true;
	while (StrNumber[StrNumber.size() - 1] == '0' || StrNumber[StrNumber.size() - 1] == '.' || StrNumber[StrNumber.size() - 1] == '9') {

		if (StrNumber[StrNumber.size() - 1] == '0') {
			if (!decimal)
				break;
			decimalSize--;
			StrNumber.pop_back();
			nines = false;
		}
		else if (StrNumber[StrNumber.size() - 1] == '9') {
			if (nines)
				StrNumber.pop_back();
			else break;
			decimalSize--;
		}
		else {
			decimal = false;
			StrNumber.pop_back();
			if(!nines)
				break;
		}
	}
	bool stupidcase = false;
	if (nines) {
		if (StrNumber.size())
			StrNumber[StrNumber.size() - 1] += 1;
		else {
			StrNumber.push_back('1');
			stupidcase = true;
		}
		while (!decimal && integerSize > (int)StrNumber.size())
			StrNumber.push_back('0');
		if(stupidcase)
			StrNumber.push_back('0');
	}

	updateText();
}

void DecimalBar::setFont(Font f)
{
	font = f;
	TextNumber.setFont(font);
}

void DecimalBar::setPosition(Vector2f position)
{
	Position = position;
	Holder.setPosition(Position);
	TextNumber.setPosition(Position.x + Dimensions.x - TextNumber.getLocalBounds().width - 3.f, Position.y + 2.f);
}

float DecimalBar::getNumber()
{
	return Number;
}

Sprite DecimalBar::getSprite()
{
	return Holder;
}

void DecimalBar::setNumberFromString()
{
	std::string stringCopy = StrNumber;
	Number = 0;
	if (decimal) {
		for (int i = decimalSize; i > 0; i--) {
			Number += float(stringCopy[stringCopy.size() - 1] - 48) / float(pow(10, i));
			stringCopy.pop_back();
		}
		stringCopy.pop_back();
	}
	for (int i = 0; i < integerSize; i++) {
		Number += float(stringCopy[stringCopy.size() - 1] - 48) * float(pow(10, i));
		stringCopy.pop_back();
	}
}

void DecimalBar::updateText()
{
	TextNumber.setString(StrNumber);
	TextNumber.setPosition(Position.x + Dimensions.x - TextNumber.getLocalBounds().width - 4.f, Position.y + 2.f);
}

int DecimalBar::EventCheck(Event& event, Vector2i MousePos)
{
	if (Keyboard::isKeyPressed(Keyboard::Enter) && Pressed) {
		Pressed = false;
		SetTexture(Holder, TexHolder[0]);
		setNumberFromString();
		return 1;
	}
	if (InsideRectangle(MousePos, Position, Dimensions)) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			SetTexture(Holder, TexHolder[2]);
			Pressed = true;
			JustPressed = true;
		}
		else if (!Pressed)
			SetTexture(Holder, TexHolder[1]);
	}
	else {
		if (Mouse::isButtonPressed(Mouse::Left) && Pressed) {
			Pressed = false;
			SetTexture(Holder, TexHolder[0]);
			setNumberFromString();
			return 1;
		}
		else if (!Pressed)
			SetTexture(Holder, TexHolder[0]);
	}
	if (Pressed && event.type == Event::TextEntered) {
		char c = event.text.unicode;
		if (c == 8) {
			if (StrNumber[StrNumber.size()-1] == '.')
				decimal = false;
			else if (decimal)
				decimalSize--;
			else if (integerSize)
				integerSize--;
			StrNumber.pop_back();
			if (!StrNumber.size())
				StrNumber.push_back('0');
			updateText();
		}
		if (c == '.' && !decimal && MaxDecimals) {
			StrNumber.push_back('.');
			decimal = true;
			decimalSize = 0;
			updateText();
		}
		if (c >= 48 && c <= 57) {
			if ((!integerSize && !decimal && c == '0') ||
				(decimal && decimalSize == MaxDecimals) ||
				(!decimal && integerSize == MaxIntegers) ||
				integerSize + decimalSize == MaxFigures)
				return 0;
			if (!integerSize && !decimal)
				StrNumber.pop_back();
			StrNumber.push_back(c);
			if (decimal)
				decimalSize++;
			else
				integerSize++;
			updateText();
		}
	}
	return 0;
}

void DecimalBar::Render(RenderWindow& window)
{
	window.draw(Holder);
	window.draw(TextNumber);
}
