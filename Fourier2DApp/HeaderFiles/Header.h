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

#define SelectorInitializer		TexturesFile, std::vector<Vector2i>({ Vector2i(0,429),Vector2i(0,456), Vector2i(0,483), Vector2i(147,429),Vector2i(147,456), Vector2i(147,483) ,Vector2i(0,512),Vector2i(147,512),Vector2i(0,536) }), std::vector<Vector2i>({ Vector2i(124,24),Vector2i(122,19) ,Vector2i(122,2) })
#define InvisibleSelector		TexturesFile, std::vector<Vector2i>({ Vector2i(160,175),Vector2i(160,175), Vector2i(160,175), Vector2i(160,175),Vector2i(160,175), Vector2i(160,175) ,Vector2i(0,512),Vector2i(147,512),Vector2i(0,536) }), std::vector<Vector2i>({ Vector2i(124,23),Vector2i(122,19) ,Vector2i(122,2) })

using namespace sf;