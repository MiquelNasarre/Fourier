#include "Scroller.h"

Vector2f Scroller::calculatePos(int n)
{
	return Vector2f(Position.x, Position.y + (float)atan(float(n - CurrentSelected) / 1.5) * 40);
}

//	Public

Scroller::Scroller(Vector2f position)
	: Position{ position },
	BigAddButton	{ Button(BigAddButtonInitializer, Position)		},
	AddDown			{ Button(AdDownButtonInitializer, AddDownPos)	},
	AddUp			{ Button(AddUpButtonInitializer, AddUpPos)		},
	Delete			{ Button(CrossButtonInitializer, DeletePos)		},
	ScrollerSelector{ Selector(InvisibleSelector,Position)			}
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
	Tracker = other.Tracker;
}

void Scroller::setPosition(Vector2f position)
{
	Position = position;
	BigAddButton.setPosition(position);
	AddDown.setPosition(AddDownPos);
	AddUp.setPosition(AddUpPos);
	Delete.setPosition(DeletePos);
}

void Scroller::pushBack(std::string Name, void* ID)
{
	Selections.push_back(Button(TextButtonInitializer, Position, true, Name, Vector2f(10.f, 3.f), font, 12));
	Tracker.push_back(ID);
	if (CurrentSelected == -1)
		CurrentSelected++;
}

std::vector<void*> Scroller::getTracker()
{
	return Tracker;
}

bool Scroller::TrackerUpdate(std::vector<void*> OptionsPointer, std::vector<void*>& track)
{
	bool update = false;
	for (int i = 0; i < (int)Tracker.size(); i++) {
		if (Tracker[i] && std::find(OptionsPointer.begin(), OptionsPointer.end(), Tracker[i]) == OptionsPointer.end()) {
			Tracker.erase(Tracker.begin() + i);
			Selections.erase(Selections.begin() + i);
			for (int j = 0; j < (int)Selections.size(); j++)
				Selections[j].setPosition(calculatePos(j));
			if (CurrentSelected >= i && CurrentSelected)
				CurrentSelected--;
			update = true;
		}
	}
	track = Tracker;
	return update;
}

int Scroller::EventCheck(Vector2i MousePos, std::vector<std::string> Options, std::vector<void*> OptionsPointer, std::vector<void*>& track)
{
	TrackerUpdate(OptionsPointer, track);
	for (int i = 0; i < (int)Selections.size(); i++) {
		if (Tracker[i])
			Selections[i].setString(Options[std::find(OptionsPointer.begin(), OptionsPointer.end(), Tracker[i]) - OptionsPointer.begin()]);
	}
		
	if (!Mouse::isButtonPressed(Mouse::Left))
		pressing = false;
	if (pressing)
		return 0;
	if (Mouse::isButtonPressed(Mouse::Left))
		pressing = true;

	if (ScrollerSelector.IsOpen) {
		ScrollerSelector.clear();
		for (int i = 0; i < (int)Options.size(); i++)
			ScrollerSelector.pushBack(Options[i]);
		ScrollerSelector.setCurrentSelected(-1);
		int selectorEvent = ScrollerSelector.EventCheck(MousePos);
		if (selectorEvent >= 0) {
			pressing = true;
			Selections[CurrentSelected].setString(ScrollerSelector.getString(ScrollerSelector.getCurrentSelected()));
			Tracker[CurrentSelected] = OptionsPointer[selectorEvent];
			ScrollerSelector.clear();
			track = Tracker;
		}
		if (selectorEvent >= -1)
			return 1;
		return 0;
	}

	if (!Selections.size() && BigAddButton.EventCheck(MousePos) == Button::Pressed) {
		Selections.push_back(Button(TextButtonInitializer, Position, true, "", Vector2f(10.f, 3.f), font,12));
		Tracker.push_back(NULL);
		ScrollerSelector.Open();
		CurrentSelected = 0;
		BigAddButton.setState(Button::NoState);
	}
	if (Selections.size()) {
		Selections[CurrentSelected].setTexture(0);

		int ButtonState = AddDown.EventCheck(MousePos);
		if (ButtonState == Button::Pressed) {
			Selections.insert(Selections.begin() + CurrentSelected + 1, Button(TextButtonInitializer, Position, true, "", Vector2f(10.f, 3.f), font, 12));
			Tracker.insert(Tracker.begin() + CurrentSelected + 1, NULL);
			CurrentSelected++;
			ScrollerSelector.Open();
			for (int i = 0; i < (int)Selections.size(); i++)
				Selections[i].setPosition(calculatePos(i));
			return 1;
		}
		else if (ButtonState == Button::Hovered || ButtonState == Button::Hovering) {
			if (CurrentSelected < (int)Selections.size() - 1)
				Selections[CurrentSelected + 1].setTexture(0);
			return 1;
		}
		ButtonState = AddUp.EventCheck(MousePos);
		if (ButtonState == Button::Pressed) {
			Selections.insert(Selections.begin() + CurrentSelected, Button(TextButtonInitializer, Position,true,"",Vector2f(10.f,3.f),font,12));
			Tracker.insert(Tracker.begin() + CurrentSelected, NULL);
			ScrollerSelector.Open();
			for (int i = 0; i < (int)Selections.size(); i++)
				Selections[i].setPosition(calculatePos(i));
			return 1;
		}
		else if (ButtonState == Button::Hovered || ButtonState == Button::Hovering) {
			if (CurrentSelected)
				Selections[CurrentSelected - 1].setTexture(0);
			return 1;
		}

		if (Delete.EventCheck(MousePos) == Button::Pressed) {
			Tracker.erase(Tracker.begin() + CurrentSelected);
			Selections.erase(Selections.begin() + CurrentSelected);
			for (int i = 0; i < (int)Selections.size(); i++)
				Selections[i].setPosition(calculatePos(i));
			if (CurrentSelected)
				CurrentSelected--;
		}

		for (int i = CurrentSelected + 1; i < (int)Selections.size(); i++) {
			int ButtonEvent = Selections[i].EventCheck(MousePos);
			if (ButtonEvent == Button::Pressed) {
				CurrentSelected = i;
				pressing = true;
				return i + 2;
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
				return i + 2;
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
	return 0;
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
	if (!ScrollerSelector.IsOpen)
		Delete.Render(renderer);
	if(ScrollerSelector.IsOpen)
		ScrollerSelector.Render(renderer);
}
