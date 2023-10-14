#include "Settings.h"

Settings::Settings()
	:Play			{ Button(PlayButtonInitializer,Vector2f(55.f, 265.f)) },
	Pause			{ Button(StopButtonInitializer,Vector2f(55.f, 265.f)) },
	IncreaseSpeed	{ Button(PrevButtonInitializer,Vector2f(102.f,266.f)) },
	DecreaseSpeed	{ Button(NextButtonInitializer,Vector2f(32.f, 266.f)) },
	Draw			{ Button(BigButtonInitializer ,Vector2f(9.f, 165.f),true,"Draw",Vector2f(18.f,4.f),Font(),12) },
	Save			{ Button(BlueButtonInitializer,Vector2f(81.f,195.f),true,"Save",Vector2f(19.f,4.f),Font(),12) },
	Load			{ Button(BlueButtonInitializer,Vector2f(9.f, 195.f),true,"Load",Vector2f(20.f,4.f),Font(),12) },
	Show			{ Button(BigButtonInitializer ,Vector2f(81.f,165.f),true,"Show",Vector2f(18.f,4.f),Font(),12) },
	Hide			{ Button(BigButtonInitializer ,Vector2f(81.f,165.f),true,"Hide",Vector2f(21.f,4.f),Font(),12) },
	DataWindow		{ Button(TextButtonInitializer,Vector2f(17.f, 17.f),true,"Coefficients",Vector2f(28.f,4.f),Font(),12) },
	ErrorBar		{ DecimalBar(DefaultDecimalBarInitializer,Vector2f(1.85f,1.f),Vector2f(78.f,50.f)) },
	NumberPoints	{ DecimalBar(DefaultDecimalBarInitializer,Vector2f(1.85f,1.f),Vector2f(78.f,80.f),10,Font(),0,4,4) }
{
	font.loadFromFile(ArialFontFile);
	ErrorBar.setFont(font);
	ErrorBar.setNumber(error);
	NumberPoints.setFont(font);
	NumberPoints.setNumber((float)points);
	DataWindow.setFont(font);
	Draw.setFont(font);
	Save.setFont(font);
	Load.setFont(font);
	Show.setFont(font);
	Hide.setFont(font);
	
	Text text;
	text.setFont(font);
	text.setCharacterSize(13);
	text.setFillColor(Color::Black);

	text.setString("Error:");
	text.setPosition(Vector2f(10.f, 55.f));
	texts.push_back(text);

	text.setString("Points:");
	text.setPosition(Vector2f(10.f, 85.f));
	texts.push_back(text);

	text.setString("Discrete error:");
	text.setPosition(Vector2f(10.f, 115.f));
	texts.push_back(text);

	text.setString("");
	text.setPosition(Vector2f(105.f, 115.f));
	texts.push_back(text);

	text.setString("Coefficients:");
	text.setPosition(Vector2f(10.f, 140.f));
	texts.push_back(text);

	text.setString("");
	text.setPosition(Vector2f(105.f, 140.f));
	texts.push_back(text);

	Image image;
	image.loadFromFile(TexturesFile);
	TexHoder.loadFromImage(image, IntRect(0, 131, 156, 293));
	Holder.setTexture(TexHoder);
	Holder.setPosition(0.f, 10.f);
}

void Settings::render(RenderWindow& window)
{
	window.draw(Holder);
	for (unsigned int i = 0; i < texts.size(); i++)
		window.draw(texts[i]);

	if (playing)
		Pause.Render(window);
	else
		Play.Render(window);

	if (pointsVisible)
		Hide.Render(window);
	else
		Show.Render(window);

	IncreaseSpeed.Render(window);
	DecreaseSpeed.Render(window);
	DataWindow.Render(window);
	ErrorBar.Render(window);
	NumberPoints.Render(window);
	Draw.Render(window);
	Save.Render(window);
	Load.Render(window);
}
