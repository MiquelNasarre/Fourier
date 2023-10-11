#include "Settings.h"

Settings::Settings()
	:Play		{ Button(PlayButtonInitializer,Vector2f(10.f, 10.f)) },
	Pause		{ Button(StopButtonInitializer,Vector2f(10.f, 10.f)) },
	DataWindow	{ Button(BigButtonInitializer ,Vector2f(10.f,605.f)) },
	ErrorBar	{ NumberBar(DefaultNumberBarInitializer,Vector2f(100.f,100.f),255,0,20) }
{
	Font font;
	font.loadFromFile(ArialFontFile);
	ErrorBar.setFont(font);
	ErrorBar.setNumber(35);
}

void Settings::render(RenderWindow& window)
{
	if (playing)
		Pause.Render(window);
	else
		Play.Render(window);

	DataWindow.Render(window);
	ErrorBar.Render(window);
}
