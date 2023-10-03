#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

#define NumOfTexturesButtons 3
#define ArialFontFile "Resources/Fonts/arial.ttf"
#define TexturesFile "Resources/Textures/CustomButtons.png"
#define BigButtonInitializer	TexturesFile, std::vector{ Vector2i(  0, 3),Vector2i(  0,36),Vector2i(  0,69) }, Vector2i(89, 32), Vector2f(.75f,.75f)
#define RedButtonInitializer	TexturesFile, std::vector{ Vector2i(157, 3),Vector2i(157,36),Vector2i(157,69) }, Vector2i(89, 32), Vector2f(.75f,.75f)
#define BlueButtonInitializer	TexturesFile, std::vector{ Vector2i(269, 3),Vector2i(269,36),Vector2i(269,69) }, Vector2i(89, 32), Vector2f(.75f,.75f)
#define UpButtonInitializer		TexturesFile, std::vector{ Vector2i(112, 3),Vector2i(112,36),Vector2i(112,69) }, Vector2i(38, 16), Vector2f(1.f, 0.7f)
#define DownButtonInitializer	TexturesFile, std::vector{ Vector2i(112,19),Vector2i(112,52),Vector2i(112,85) }, Vector2i(38, 16), Vector2f(1.f, 0.7f)
#define ColorButtonInitializer	TexturesFile, std::vector{ Vector2i(285,430),Vector2i(309,430),Vector2i(333,430) }, Vector2i(22, 22), Vector2f(1.f, 1.f)
#define PlusButtonInitializer	TexturesFile, std::vector{ Vector2i(559,444),Vector2i(559,471),Vector2i(559,498) }, Vector2i(20, 20), Vector2f(1.f, 1.f)
#define BigAddButtonInitializer	TexturesFile, std::vector{ Vector2i(419,14),Vector2i(419,41),Vector2i(419,68) }, Vector2i(123, 23), Vector2f(1.f, 1.f)
#define TextButtonInitializer	TexturesFile, std::vector{ Vector2i(556,14),Vector2i(556,41),Vector2i(556,68) }, Vector2i(123, 23), Vector2f(1.f, 1.f)
#define AddUpButtonInitializer	TexturesFile, std::vector{ Vector2i(704, 7),Vector2i(704,38),Vector2i(704,69) }, Vector2i( 46, 12), Vector2f(1.f, 1.f)
#define AdDownButtonInitializer	TexturesFile, std::vector{ Vector2i(704,21),Vector2i(704,52),Vector2i(704,83) }, Vector2i( 46, 12), Vector2f(1.f, 1.f)
#define PlayButtonInitializer	TexturesFile, std::vector{ Vector2i(805, 7),Vector2i(805,38),Vector2i(805,69) }, Vector2i( 45, 29), Vector2f(1.f, 1.f)
#define StopButtonInitializer	TexturesFile, std::vector{ Vector2i(882, 7),Vector2i(882,38),Vector2i(882,69) }, Vector2i( 45, 29), Vector2f(1.f, 1.f)
#define BackButtonInitializer	TexturesFile, std::vector{ Vector2i(778, 7),Vector2i(778,38),Vector2i(778,69) }, Vector2i( 27, 29), Vector2f(1.f, 1.f)
#define FrwdButtonInitializer	TexturesFile, std::vector{ Vector2i(850, 7),Vector2i(850,38),Vector2i(850,69) }, Vector2i( 27, 29), Vector2f(1.f, 1.f)
#define NextButtonInitializer	TexturesFile, std::vector{ Vector2i(757, 8),Vector2i(757,39),Vector2i(757,70) }, Vector2i( 21, 27), Vector2f(1.f, 1.f)
#define PrevButtonInitializer	TexturesFile, std::vector{ Vector2i(927, 8),Vector2i(927,39),Vector2i(927,70) }, Vector2i( 21, 27), Vector2f(1.f, 1.f)
#define CrossButtonInitializer	TexturesFile, std::vector{ Vector2i(374,50),Vector2i(374,69),Vector2i(390,50) }, Vector2i( 12, 12), Vector2f(1.f, 1.f)

#define InvisibleButton(x,y)	TexturesFile, std::vector{Vector2i(0,0),Vector2i(0,0),Vector2i(0,0)},Vector2i(x,y),Vector2f(1.f,1.f)


#define SelectorInitializer		TexturesFile, std::vector<Vector2i>({ Vector2i(0,429),Vector2i(0,456), Vector2i(0,483), Vector2i(147,429),Vector2i(147,456), Vector2i(147,483) ,Vector2i(0,512),Vector2i(147,512),Vector2i(0,536) }), std::vector<Vector2i>({ Vector2i(124,24),Vector2i(122,19) ,Vector2i(122,2) })
#define InvisibleSelector		TexturesFile, std::vector<Vector2i>({ Vector2i(160,175),Vector2i(160,175), Vector2i(160,175), Vector2i(160,175),Vector2i(160,175), Vector2i(160,175) ,Vector2i(0,512),Vector2i(147,512),Vector2i(0,536) }), std::vector<Vector2i>({ Vector2i(124,23),Vector2i(122,19) ,Vector2i(122,2) })

using namespace sf;