#pragma once

#include "Header.h"
#include "Objects.h"

#define InitialWinPos   Vector2i(86,25)
#define ScreenWidth     1180
#define ScreenHeight    640
#define Ex -7
#define Ey 30
#define DistanceGrid 0.5f
#define GridColor Color(170,170,170,255)
#define MaxScale 1000
#define MinScale 10

class Renderer
{
private:
    RenderTarget& m_target;
    float Scale = 200;
    Vector2i WindowPos;
    Font font;

public:
    Renderer(RenderTarget& target);

    void SetWindowPos(Vector2i WinPos);
    void renderPlain(Vector2i Pos) const;
    void ModifyScale(float increment);
    float getScale();

    static Vector2f R2Pos(Vector2i Pos, Vector2i ScreenPos, float scale);
    static Vector2f R2Pos(Vector2f Pos, float Radius, float scale);
    static Vector2f ScPos(Vector2f Pos, float Radius, float scale);

    void RenderMousePosition(Vector2i Pos) const;
    void RenderGrid() const;
    void RenderAxis() const;
    void RenderPoint(Point P, int i) const;
    void RenderFunction(PixelFunction& Function) const;
    void RenderCircleDescription(Point P, int n) const;
    void RenderSprite(Sprite& sprite) const;
    void RenderText(Text text);
};
