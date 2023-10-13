#pragma once

#include "Header.h"
#include "Renderer.h"

#define NumOfTexturesButtons 3

#define BigButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(  0, 3),Vector2i(  0,36),Vector2i(  0,69) }, Vector2i(89, 32), Vector2f(.75f,.75f)
#define RedButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(157, 3),Vector2i(157,36),Vector2i(157,69) }, Vector2i(89, 32), Vector2f(.75f,.75f)
#define BlueButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(269, 3),Vector2i(269,36),Vector2i(269,69) }, Vector2i(89, 32), Vector2f(.75f,.75f)
#define UpButtonInitializer		TexturesFile, std::vector<Vector2i>{ Vector2i(112, 3),Vector2i(112,36),Vector2i(112,69) }, Vector2i(38, 16), Vector2f(1.f, 0.7f)
#define DownButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(112,19),Vector2i(112,52),Vector2i(112,85) }, Vector2i(38, 16), Vector2f(1.f, 0.7f)
#define BigAddButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(419,14),Vector2i(419,41),Vector2i(419,68) }, Vector2i(123, 23), Vector2f(1.f, 1.f)
#define TextButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(556,14),Vector2i(556,41),Vector2i(556,68) }, Vector2i(123, 23), Vector2f(1.f, 1.f)
#define AddUpButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(704, 7),Vector2i(704,38),Vector2i(704,69) }, Vector2i( 46, 12), Vector2f(1.f, 1.f)
#define AdDownButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(704,21),Vector2i(704,52),Vector2i(704,83) }, Vector2i( 46, 12), Vector2f(1.f, 1.f)
#define PlayButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(805, 7),Vector2i(805,38),Vector2i(805,69) }, Vector2i( 45, 29), Vector2f(1.f, 1.f)
#define StopButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(882, 7),Vector2i(882,38),Vector2i(882,69) }, Vector2i( 45, 29), Vector2f(1.f, 1.f)
#define BackButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(778, 7),Vector2i(778,38),Vector2i(778,69) }, Vector2i( 27, 29), Vector2f(1.f, 1.f)
#define FrwdButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(850, 7),Vector2i(850,38),Vector2i(850,69) }, Vector2i( 27, 29), Vector2f(1.f, 1.f)
#define NextButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(757, 8),Vector2i(757,39),Vector2i(757,70) }, Vector2i( 21, 27), Vector2f(1.f, 1.f)
#define PrevButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(927, 8),Vector2i(927,39),Vector2i(927,70) }, Vector2i( 21, 27), Vector2f(1.f, 1.f)
#define CrossButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(374,50),Vector2i(374,69),Vector2i(390,50) }, Vector2i( 12, 12), Vector2f(1.f, 1.f)
#define ToolsButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(671,115),Vector2i(671,147),Vector2i(671,179) }, Vector2i(32, 26), Vector2f(1.f, 1.f)
#define ColorButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(285,430),Vector2i(309,430),Vector2i(333,430) }, Vector2i(22, 22), Vector2f(1.f, 1.f)
#define PlusButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(559,444),Vector2i(559,471),Vector2i(559,498) }, Vector2i(20, 20), Vector2f(1.f, 1.f)
#define UpperButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(699,241),Vector2i(783,241),Vector2i(867,241) }, Vector2i(30, 26), Vector2f(1.f, 1.f)
#define DownerButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(699,297),Vector2i(783,297),Vector2i(867,297) }, Vector2i(30, 26), Vector2f(1.f, 1.f)
#define LeftButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(673,267),Vector2i(757,267),Vector2i(841,267) }, Vector2i(26, 30), Vector2f(1.f, 1.f)
#define RightButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(729,267),Vector2i(813,267),Vector2i(897,267) }, Vector2i(26, 30), Vector2f(1.f, 1.f)
#define CenterButtonInitializer	TexturesFile, std::vector<Vector2i>{ Vector2i(699,267),Vector2i(783,267),Vector2i(867,267) }, Vector2i(30, 30), Vector2f(1.f, 1.f)

#define InvisibleButton(x,y)	TexturesFile, std::vector{Vector2i(0,0),Vector2i(0,0),Vector2i(0,0)},Vector2i(x,y),Vector2f(1.f,1.f)

class Button {
private:

	Font					textFont;
	Text					text;
	std::vector<Texture>	Textures;
	Sprite					sprite;

	Vector2f				Position;
	Vector2f				Dimensions;
	Vector2f				textPos;
	Vector2f				Scale;

	int						State = 0;
	bool					Visibility;

public:
	static const int Pressed	=  3;
	static const int Pressing	= -3;
	static const int Hovered	=  2;
	static const int Hovering	= -2;
	static const int Unhovered	=  1;
	static const int NoState	= -1;

	Button() {}
	Button(std::string TextureFile, std::vector<Vector2i> PosInFile, Vector2i SizeInFile, Vector2f scale, Vector2f position = Vector2f(0.f, 0.f), bool Draw = true, std::string textStr = "", Vector2f textPosition = Vector2f(0.f, 0.f), Font font = Font(), int characterSize = 14, Color FillColor = Color::Black);
	Button(const Button& other);

	Vector2f GetPosition();
	Vector2f GetDimensions();
	int GetState();
	bool GetVisibility();

	void setPosition(Vector2f Pos);
	void setPosition(float x, float y);
	void IncreasePosition(Vector2f Diff);
	void IncreasePosition(float dx, float dy);
	void setState(int s);
	void setVisibility(bool V);
	void setTexture(int t);
	void setColor(Color color);

	void setTextures(std::vector<Texture> textures);
	void setFont(Font font);
	void setString(std::string String);

	int eventCheck(Vector2i MouseScPos);
	void Render(RenderWindow& window);
};
