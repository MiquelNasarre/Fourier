#include "Scroller.h"

Vector2f Scroller::calculatePos(int n)
{
	return Vector2f(Position.x, Position.y + (float)atan(float(n - CurrentSelected) / 1.5) * 50);
}

Scroller::Scroller(Vector2f position)
	: Position{ position },
	BigAddButton	{ Button(BigAddButtonInitializer, Position) },
	AddDown			{ Button(DownButtonInitializer, AddDownPos) },
	AddUp			{ Button(UpButtonInitializer, AddUpPos)		},
	Delete			{ Button(UpButtonInitializer, AddUpPos)		},
	ScrollerSelector{ Selector(InvisibleSelector,Position)		}
{
	ScrollerSelector.WhenToOpen(Selector::OpenNever);
	font.loadFromFile(ArialFontFile);
}


Scroller::Scroller(const Scroller& other)
	: ScrollerSelector{ other.ScrollerSelector }
{
	font = other.font;
	Position = other.Position;
	BigAddButton = other.BigAddButton;
	AddDown = other.AddDown;
	AddUp = other.AddUp;
	Delete = other.Delete;
	Selections = other.Selections;
	ScrollerPos = other.ScrollerPos;
	CurrentSelected = other.CurrentSelected;
	pressing = other.pressing;
}

void Scroller::setPosition(Vector2f position)
{
	Position = position;
	BigAddButton.setPosition(position);
	AddDown.setPosition(position);
	AddUp.setPosition(position);
}


void Scroller::EventCheck(Vector2i MousePos, std::vector<std::string> Options, std::vector<void*> OptionsPointer, std::vector<void*>& track)
{
	for (int i = 0; i < (int)Tracker.size(); i++) {
		if (Tracker[i] && std::find(OptionsPointer.begin(), OptionsPointer.end(), Tracker[i]) == OptionsPointer.end()) {
			Tracker.erase(Tracker.begin() + i);
			Selections.erase(Selections.begin() + i);
			for (int i = 0; i < (int)Selections.size(); i++)
				Selections[i].setPosition(calculatePos(i));
			if (CurrentSelected >= i && CurrentSelected)
				CurrentSelected--;
		}
	}
	track = Tracker;
	if (!Mouse::isButtonPressed(Mouse::Left))
		pressing = false;
	if (pressing)
		return;

	if (ScrollerSelector.IsOpen) {
		ScrollerSelector.RemoveAll();
		for (int i = 0; i < (int)Options.size(); i++)
			ScrollerSelector.AddOption(Options[i]);
		ScrollerSelector.SetCurrentSelected(-1);
		int selectorEvent = ScrollerSelector.EventCheck(MousePos);
		if (selectorEvent >= 0) {
			pressing = true;
			Selections[CurrentSelected].setString(ScrollerSelector.getString(ScrollerSelector.getCurrentSelected()));
			Tracker[CurrentSelected] = OptionsPointer[selectorEvent];
			ScrollerSelector.RemoveAll();
			track = Tracker;
		}
		return;
	}

	if (!Selections.size() && BigAddButton.EventCheck(MousePos) == Button::Pressed) {
		Selections.push_back(Button(TextButtonInitializer, Position, true, "", Vector2f(10.f, 3.f), font,12));
		Tracker.push_back(NULL);
		ScrollerSelector.Open();
		CurrentSelected = 0;
	}
	if (Selections.size()) {
		Selections[CurrentSelected].setTexture(0);
		if (AddDown.EventCheck(MousePos) == Button::Pressed) {
			Selections.insert(Selections.begin() + CurrentSelected + 1, Button(TextButtonInitializer, Position, true, "", Vector2f(10.f, 3.f), font, 12));
			Tracker.insert(Tracker.begin() + CurrentSelected + 1, NULL);
			CurrentSelected++;
			ScrollerSelector.Open();
			for (int i = 0; i < (int)Selections.size(); i++)
				Selections[i].setPosition(calculatePos(i));
			pressing = true;
			return;
		}
		if (AddUp.EventCheck(MousePos) == Button::Pressed) {
			Selections.insert(Selections.begin() + CurrentSelected, Button(TextButtonInitializer, Position,true,"",Vector2f(10.f,3.f),font,12));
			Tracker.insert(Tracker.begin() + CurrentSelected, NULL);
			ScrollerSelector.Open();
			for (int i = 0; i < (int)Selections.size(); i++)
				Selections[i].setPosition(calculatePos(i));
			pressing = true;
			return;
		}
		for (int i = CurrentSelected + 1; i < (int)Selections.size(); i++) {
			int ButtonEvent = Selections[i].EventCheck(MousePos);
			if (ButtonEvent == Button::Pressed) {
				CurrentSelected = i;
				pressing = true;
				break;
			}
			if (ButtonEvent == Button::Hovering || ButtonEvent == Button::Hovered) {
				for (int j = 0; j < (int)Selections.size(); j++)
					Selections[j].setTexture(0);
				Selections[i].setTexture(1);
				break;
			}
				
		}
		for (int i = CurrentSelected - 1; i >= 0; i--) {
			int ButtonEvent = Selections[i].EventCheck(MousePos);
			if (ButtonEvent == Button::Pressed) {
				CurrentSelected = i;
				pressing = true;
				break;
			}
			if (ButtonEvent == Button::Hovering || ButtonEvent == Button::Hovered) {
				for (int j = 0; j < (int)Selections.size(); j++)
					Selections[j].setTexture(0);
				Selections[i].setTexture(1);
				break;
			}

		}

		for (int i = 0; i < (int)Selections.size(); i++)
			Selections[i].setPosition(calculatePos(i));
			
	}
}

void Scroller::Render(Renderer& renderer)
{
	if (!Selections.size()) {
		BigAddButton.Render(renderer);
		return;
	}
	
	for (int i = 0; i < CurrentSelected; i++)
		Selections[i].Render(renderer);
	for (int i = Selections.size()-1; i > CurrentSelected; i--)
		Selections[i].Render(renderer);
	if (!ScrollerSelector.IsOpen) {
		AddUp.Render(renderer);
		AddDown.Render(renderer);
	}
	Selections[CurrentSelected].Render(renderer);
	ScrollerSelector.Render(renderer);
}
