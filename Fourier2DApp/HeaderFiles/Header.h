#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

#define NumOfTexturesButtons 3
#define ArialFontFile "Resources/Fonts/arial.ttf"
#define BigButtonInitializer	"Resources/Textures/CustomButtons.png", std::vector({ Vector2i(  0, 3),Vector2i(  0,36),Vector2i(  0,69) }), Vector2i(89, 32), Vector2f(.75f,.75f)
#define RedButtonInitializer	"Resources/Textures/CustomButtons.png", std::vector({ Vector2i(157, 3),Vector2i(157,36),Vector2i(157,69) }), Vector2i(89, 32), Vector2f(.75f,.75f)
#define BlueButtonInitializer	"Resources/Textures/CustomButtons.png", std::vector({ Vector2i(269, 3),Vector2i(269,36),Vector2i(269,69) }), Vector2i(89, 32), Vector2f(.75f,.75f)
#define UpButtonInitializer		"Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112, 3),Vector2i(112,36),Vector2i(112,69) }), Vector2i(38, 16), Vector2f(1.f, 0.7f)
#define DownButtonInitializer	"Resources/Textures/CustomButtons.png", std::vector({ Vector2i(112,19),Vector2i(112,52),Vector2i(112,85) }), Vector2i(38, 16), Vector2f(1.f, 0.7f)
#define ColorButtonInitializer	"Resources/Textures/CustomButtons.png", std::vector({ Vector2i(285,430),Vector2i(309,430),Vector2i(333,430) }), Vector2i(22, 22), Vector2f(1.f, 1.f)

#define SelectorInitializer		"Resources/Textures/CustomButtons.png", std::vector<Vector2i>({ Vector2i(0,429),Vector2i(0,456), Vector2i(0,483), Vector2i(147,429),Vector2i(147,456), Vector2i(147,483) ,Vector2i(0,512),Vector2i(147,512),Vector2i(0,536) }), std::vector<Vector2i>({ Vector2i(124,24),Vector2i(122,19) ,Vector2i(122,2) })

using namespace sf;