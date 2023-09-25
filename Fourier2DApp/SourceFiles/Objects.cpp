#include "Objects.h"

Button::Button(std::string TextureFile, std::vector<Vector2i> PosInFile, Vector2i SizeInFile, Vector2f scale, Vector2f position, bool Draw) {
	ToBe = Draw;
	Position = position;
	Scale = scale;
	Dimensions = Vector2f(Scale.x * SizeInFile.x, Scale.y * SizeInFile.y);

	Image image;
	Texture texture;
	image.loadFromFile(TextureFile);
	Objects::TransparentGreenScreen(&image);
	for (int i = 0; i < NumOfTexturesButtons; i++) {
		texture.loadFromImage(image, IntRect(PosInFile[i], SizeInFile));
		Textures.push_back(texture);
	}
	sprite.setTexture(Textures[0]);
	sprite.setScale(Scale);
	sprite.setPosition(position);
}

void Button::setPosition(Vector2f Pos)
{
	Position = Pos;
	sprite.setPosition(Position);
}

void Button::setPosition(float x, float y)
{
	Position = Vector2f(x, y);
	sprite.setPosition(Position);
}

void Button::IncreasePosition(Vector2f Diff) 
{
	Position = Vector2f(Position.x + Diff.x, Position.y + Diff.y);
	sprite.setPosition(Position);
}

void Button::IncreasePosition(float dx, float dy) 
{
	Position = Vector2f(Position.x + dx, Position.y + dy);
	sprite.setPosition(Position);
}

void Button::setScale(Vector2f scale) 
{
	Dimensions = Vector2f(Dimensions.x * scale.x / Scale.x, Dimensions.y * scale.y / Scale.y);
	Scale = scale;
}

void Button::setScale(float x, float y) 
{
	Dimensions = Vector2f(Dimensions.x * x / Scale.x, Dimensions.y * y / Scale.y);
	Scale = Vector2f(x, y);
}



void Objects::InitializeCircles(int N, float* Radius, float* Xs, float* Ys, RGBA* Col)
{
	NumOfCircles = N;
	Circles = (CircleStr*)calloc(sizeof(CircleStr), N);
	for (int i = 0; i < N; i++) {
		Circles[i].Radius = Radius[i];
		Circles[i].Position.x = Xs[i];
		Circles[i].Position.y = Ys[i];
		Circles[i].Color = Col[i];
	}

}

void Objects::SetCirclePos(int n, float x, float y)
{
	Circles[n].Position.x = x;
	Circles[n].Position.y = y;
	return;
}

void Objects::SetCircleRadius(int n, float r)
{
	Circles[n].Radius = r;
	return;
}

void Objects::SetCircleColor(int n, RGBA c)
{
	Circles[n].Color = c;
	return;
}

void Objects::SetCircleDescription(int n, bool d)
{
	Circles[n].Description = d;
	return;
}

void Objects::SetDescriptionsFalse()
{
	for (int i = 0; i < NumOfCircles; i++)
		Circles[i].Description = false;
	return;
}

Vector2f Objects::GetCirclePos(int n)
{
	return Circles[n].Position;
}

float Objects::GetCircleRadius(int n)
{
	return Circles[n].Radius;
}

RGBA Objects::GetCircleColor(int n)
{
	return Circles[n].Color;
}

bool Objects::GetCircleDescription(int n)
{
	return Circles[n].Description;
}

void Objects::InitializeButtons()
{
	
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112, 3),Vector2i(112,36),Vector2i(112,69) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f, 37.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112,19),Vector2i(112,52),Vector2i(112,85) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f, 49.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112, 3),Vector2i(112,36),Vector2i(112,69) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f, 65.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112,19),Vector2i(112,52),Vector2i(112,85) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f, 77.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112, 3),Vector2i(112,36),Vector2i(112,69) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f, 93.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112,19),Vector2i(112,52),Vector2i(112,85) }), Vector2i(38, 16), Vector2f(1.f, 0.7f), Vector2f(112.f - 120.f,105.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(0,3),Vector2i(0,36),Vector2i(0,69) }), Vector2i(89, 32), Vector2f(0.75f, 0.75f), Vector2f(7.f - 120.f, 120.f), false));
	Buttons.push_back(Button("Resources/Textures/CustomButtons.png", std::vector({ Vector2i(0,3),Vector2i(0,36),Vector2i(0,69) }), Vector2i(89, 32), Vector2f(0.75f, 0.75f), Vector2f(83.f - 120.f, 120.f), false));

	NumOfButtons = Buttons.size();
}

Button* Objects::getButton(int i)
{
	return &Buttons[i];
}

void Objects::AddFunction(int n, float* x, float* y, RGBA* Col) {
	int N = NumOfFunctions++;
	Functions = (PixelFunction*)realloc(Functions, sizeof(PixelFunction) * NumOfFunctions);
	Functions[N].N = n;
	Functions[N].Color = Col;
	Functions[N].x = x;
	Functions[N].y = y;
}

void Objects::ModifyFunction(int N, int n, float* x, float* y, RGBA* Col)
{
	Functions[N].N = n;
	Functions[N].Color = Col;
	Functions[N].x = x;
	Functions[N].y = y;
}

PixelFunction* Objects::GetFunction(int n)
{
	return &Functions[n];
}

void Objects::TransparentGreenScreen(Image* image)
{
	for (unsigned int i = 0; i < image->getSize().x; i++) {
		for (unsigned int j = 0; j < image->getSize().y; j++) {
			if (image->getPixel(i, j) == Color(0, 255, 0, 255)) {
				image->setPixel(i, j, Color::Transparent);
			}
		}
	}
}
