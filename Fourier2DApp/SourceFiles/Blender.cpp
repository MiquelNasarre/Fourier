#include "Blender.h"

void Blender::MenuMovements(int& change, int fourier)
{
	if (fourier < 2 && Menu.getColor().a == 255) {
		Close();
		Menu.setColor(Color(255, 255, 255, 150));
		change = 1;
	}
	if (fourier >= 2 && Menu.getColor().a < 255) {
		Menu.setColor(Color(255, 255, 255, 255));
		change = 1;
	}
	if (OpenMenu) {
		SetTexture(Menu, MenuTextures[1]);
		if (MenuPos.x > DefaultBlenderPos.x - 120.f) {
			MoveBlender(-10.f, 0.f);
			change = 1;
		}
	}
	else {
		SetTexture(Menu, MenuTextures[0]);
		if (MenuPos.x < DefaultBlenderPos.x) {
			MoveBlender(10.f, 0.f);
			change = 1;
		}
	}
}

void Blender::MoveBlender(float dx, float dy)
{
	MenuPos = IncreaseVector(MenuPos, dx, dy);
	Menu.setPosition(MenuPos);
	MenuButton.setPosition(MenuPos);
	MainSelector.setPosition(MainSelectorPos);
	AddBlenderButton.setPosition(AddBlenderButtonPos);
}

void Blender::NewBlender()
{
	MainSelector.AddOption(Popup::InputString());
	TimeFouriers.push_back(TimeFourier());
}

//	Public

Blender::Blender() 
	: MenuButton		{ Button(InvisibleButton(34,28),DefaultBlenderPos)  },
	MainSelector		{ Selector(SelectorInitializer,MainSelectorPos)     },
	AddBlenderButton	{ Button(PlusButtonInitializer,AddBlenderButtonPos) },
	BigAddButton		{ Button() }
{
	OpenMenu = false;
	MenuPos = DefaultBlenderPos;

	Image image;
	image.loadFromFile(TexturesFile);
	TransparentGreenScreen(&image);
	Texture texture;
	texture.loadFromImage(image, IntRect(323, 104, 157, 243));
	MenuTextures.push_back(texture);
	texture.loadFromImage(image, IntRect(480, 104, 157, 243));
	MenuTextures.push_back(texture);
	Menu.setTexture(MenuTextures[0]);
	Menu.setColor(Color(255, 255, 255, 150));
	Menu.setPosition(MenuPos);

}

void Blender::Open()
{
	OpenMenu = true;
}

void Blender::Close()
{
	OpenMenu = false;
}

int Blender::EventCheck(Vector2i MousePos, std::vector<Fourier>& fouriers)
{
	int change = 0;
	MenuMovements(change, fouriers.size());
	if (fouriers.size() < 2)
		return change;

	if (MenuButton.EventCheck(MousePos) == 3) {
		if (OpenMenu)
			Close();
		else
			Open();
	}

	int iAddButton = AddBlenderButton.EventCheck(MousePos);
	if (iAddButton > 0)
		change = 1;
	if (iAddButton == 3)
		NewBlender();

	if (MainSelector.EventCheck(MousePos) >= -1)
		change = 1;

	for (int i = 0; i < (int)TimeFouriers.size(); i++) {
		if (TimeFouriers[i].UpdatePlot())
			change = 1;
	}

	return change;
}

void Blender::Render(Renderer& renderer)
{
	renderer.RenderSprite(Menu);
	for (int i = 0; i < (int)TimeFouriers.size(); i++)
		TimeFouriers[i].Render(renderer);
	if (!OpenMenu)
		return;
	MainSelector.Render(renderer);
	AddBlenderButton.Render(renderer);
}

void Blender::Render(RenderWindow& window)
{
	window.draw(Menu);
	if (!OpenMenu)
		return;
	MainSelector.Render(window);
	AddBlenderButton.Render(window);
}
