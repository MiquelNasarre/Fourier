#pragma once

#include <iostream>
#include <math.h>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

#define ArialFontFile "Resources/Fonts/arial.ttf"
#define TexturesFile "Resources/Textures/CustomButtons.png"

//#define DarkTheme

using namespace sf;

void TransparentGreenScreen(Image* image);

bool SetTexture(Sprite& sprite, Texture& texture);

bool InsideRectangle(Vector2i MousePos, Vector2f Position, Vector2i Size);

bool InsideCircle(Vector2i MousePos, Vector2f Position, int radius);

Vector2f operator+(const Vector2f& v0, const Vector2f& v1);

Vector2i operator+(const Vector2i& v0, const Vector2i& v1);

Vector2f operator*(const Vector2f& v0, const Vector2f& v1);

Vector2f operator*(const Vector2f& v0, const float& x);

Vector2f operator/(const Vector2f& v0, const float& x);

