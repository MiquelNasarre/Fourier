#include "Blender.h"

void Blender::MenuMovements(int& change, int fourier)
{
	if (fourier < 2 && Menu.getColor().a == 255) {
		Close();
		Menu.setColor(Color(255, 255, 255, 150));
		scrollers.clear();
		MainSelector.RemoveAll();
		TimeFouriers.clear();
		currentBlender = -1;
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
	for (int i = 0; i < (int)scrollers.size(); i++)
		scrollers[i].setPosition(ScrollerBlenderPos);
	PlayButton.setPosition(PlayButtonPos);
	StopButton.setPosition(PlayButtonPos);
	GoBack.setPosition(BackButtonPos);
	GoForward.setPosition(ForwardButtonPos);
	Increase.setPosition(IncreaseButtonPos);
	Decrease.setPosition(DecreaseButtonPos);
	HideAll.setPosition(HideAllButtonPos);
	ShowAll.setPosition(ShowAllButtonPos);
	Reset.setPosition(ResetButtonPos);
	Delete.setPosition(DeleteButtonPos);
}

void Blender::NewBlender()
{
	MainSelector.AddOption(Popup::InputString());
	TimeFouriers.push_back(TimeFourier());
	scrollers.push_back(Scroller(ScrollerBlenderPos));
	currentBlender = scrollers.size() - 1;
	TimeFouriers[currentBlender].setSmoothness(500);
	TimePlaying = false;
}

//	Public

Blender::Blender() 
	: MenuButton		{ Button(InvisibleButton(34,28),DefaultBlenderPos)  },
	MainSelector		{ Selector(SelectorInitializer,MainSelectorPos)     },
	AddBlenderButton	{ Button(PlusButtonInitializer,AddBlenderButtonPos) },
	PlayButton			{ Button(PlayButtonInitializer,PlayButtonPos)		},
	StopButton			{ Button(StopButtonInitializer,PlayButtonPos)		},
	GoBack				{ Button(BackButtonInitializer,BackButtonPos)		},		
	GoForward			{ Button(FrwdButtonInitializer,ForwardButtonPos)	},	
	Increase			{ Button(NextButtonInitializer,IncreaseButtonPos)	},	
	Decrease			{ Button(PrevButtonInitializer,DecreaseButtonPos)	},
	HideAll				{ Button(BigButtonInitializer,HideAllButtonPos, true, "Hide All", Vector2f(13.f, 4.f),Font(),12) },
	ShowAll				{ Button(BigButtonInitializer,ShowAllButtonPos, true, "Show All", Vector2f(11.f, 4.f),Font(),12) },
	Reset				{ Button(BigButtonInitializer,ResetButtonPos,   true, "Reset"   , Vector2f(17.f, 4.f),Font(),12) },
	Delete				{ Button(BigButtonInitializer,DeleteButtonPos,  true, "Delete  ", Vector2f(16.f, 4.f),Font(),12) }
{
	OpenMenu = false;
	MenuPos = DefaultBlenderPos;
	currentBlender = -1;
	TimePlaying = false;
	Pressing = false;

	Image image;
	image.loadFromFile(TexturesFile);
	TransparentGreenScreen(&image);
	Texture texture;
	texture.loadFromImage(image, IntRect(323, 104, 157, 321));
	MenuTextures.push_back(texture);
	texture.loadFromImage(image, IntRect(480, 104, 157, 321));
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

	//	Important Bullshit
	if (currentBlender != -1) {

		std::vector<std::string> Names;
		for (int i = 0; i < (int)fouriers.size(); i++)
			Names.push_back(fouriers[i].getName());

		std::vector<void*> fourierPointers;
		for (int i = 0; i < (int)fouriers.size(); i++)
			fourierPointers.push_back(fouriers[i].RandomPointer);

		std::vector<void*> getOrder;

		scrollers[currentBlender].EventCheck(MousePos, Names, fourierPointers, getOrder);
		if (getOrder.size()) {
			TimeFouriers[currentBlender].deleteAll();
			for (int i = 0; i < (int)getOrder.size(); i++) {
				if (getOrder[i]) {
					Fourier* F = &fouriers[std::find(fourierPointers.begin(), fourierPointers.end(), getOrder[i]) - fourierPointers.begin()];
					TimeFouriers[currentBlender].AddCoefficients(F->getCoefficients(), F->GetFunctionColor());
				}
			}
		}
		for (int i = 0; i < (int)TimeFouriers.size(); i++) {
			if (i == currentBlender)
				continue;
			getOrder.clear();
			scrollers[i].TrackerUpdate(fourierPointers, getOrder);
			if (getOrder.size()) {
				TimeFouriers[i].deleteAll();
				for (int j = 0; j < (int)getOrder.size(); j++) {
					if (getOrder[j]) {
						Fourier* F = &fouriers[std::find(fourierPointers.begin(), fourierPointers.end(), getOrder[j]) - fourierPointers.begin()];
						TimeFouriers[i].AddCoefficients(F->getCoefficients(), F->GetFunctionColor());
					}
				}
			}
		}
	}

	for (int i = 0; i < (int)TimeFouriers.size(); i++) {
		if (TimeFouriers[i].UpdatePlot())
			change = 1;
	}

	//	Less Important Bullshit

	if (!Mouse::isButtonPressed(Mouse::Left))
		Pressing = false;
	if (Pressing)
		return change;
	if (Mouse::isButtonPressed(Mouse::Left))
		Pressing = true;

	if (TimePlaying == false && PlayButton.EventCheck(MousePos) == Button::Pressed && currentBlender != -1 && TimeFouriers[currentBlender].StartTime())
		TimePlaying = true;

	else if (TimePlaying == true && StopButton.EventCheck(MousePos) == Button::Pressed && currentBlender != -1) {
		TimePlaying = false;
		TimeFouriers[currentBlender].StopTime();
	}

	else if (GoBack.EventCheck(MousePos) == Button::Pressed && currentBlender != -1)
		TimeFouriers[currentBlender].Back();

	else if (GoForward.EventCheck(MousePos) == Button::Pressed && currentBlender != -1)
		TimeFouriers[currentBlender].Forward();

	else if (Increase.EventCheck(MousePos) == Button::Pressed && currentBlender != -1)
		TimeFouriers[currentBlender].IncreaseSpeed(0.8f);

	else if (Decrease.EventCheck(MousePos) == Button::Pressed && currentBlender != -1)
		TimeFouriers[currentBlender].IncreaseSpeed(1.25f);

	else if (HideAll.EventCheck(MousePos) == Button::Pressed) {
		for (int i = 0; i < (int)fouriers.size(); i++) {
			fouriers[i].SetPointsVisibility(false);
			fouriers[i].SetFunctionVisibility(false);
		}
	}

	else if (ShowAll.EventCheck(MousePos) == Button::Pressed) {
		for (int i = 0; i < (int)fouriers.size(); i++) {
			fouriers[i].SetPointsVisibility(true);
			fouriers[i].SetFunctionVisibility(true);
		}
	}

	else if (Reset.EventCheck(MousePos) == Button::Pressed && currentBlender != -1)
		TimeFouriers[currentBlender].Restart();

	else if (Delete.EventCheck(MousePos) == Button::Pressed && currentBlender != -1) {
		TimeFouriers.erase(TimeFouriers.begin() + currentBlender);
		scrollers.erase(scrollers.begin() + currentBlender);
		MainSelector.RemoveOption();
		currentBlender--;
		return 1;
	}

	else if (MenuButton.EventCheck(MousePos) == Button::Pressed) {
		if (OpenMenu)
			Close();
		else
			Open();
	}

	else if (AddBlenderButton.EventCheck(MousePos) == Button::Pressed) {
		NewBlender();
	}

	else if (MainSelector.EventCheck(MousePos) >= -1) {
		currentBlender = MainSelector.getCurrentSelected();
	}

	change = 1;
	return change;
}

void Blender::Render(Renderer& renderer)
{
	renderer.RenderSprite(Menu);
	for (int i = 0; i < (int)TimeFouriers.size(); i++)
		TimeFouriers[i].Render(renderer);
	if (!OpenMenu)
		return;
	if (TimePlaying)
		StopButton.Render(renderer);
	else
		PlayButton.Render(renderer);

	GoBack.Render(renderer);
	GoForward.Render(renderer);
	AddBlenderButton.Render(renderer);
	Increase.Render(renderer);
	Decrease.Render(renderer);
	HideAll.Render(renderer);
	ShowAll.Render(renderer);
	Reset.Render(renderer);
	Delete.Render(renderer);


	if (currentBlender != -1)
		scrollers[currentBlender].Render(renderer);
	
	MainSelector.Render(renderer);
}

void Blender::Render(RenderWindow& window)
{
	window.draw(Menu);
	if (!OpenMenu)
		return;
	MainSelector.Render(window);
	AddBlenderButton.Render(window);
}
