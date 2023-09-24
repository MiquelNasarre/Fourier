#pragma once

#include "Header.h"
#include "Objects.h"

#define InitialWinPos   Vector2i(86,25)
#define ScreenWidth     1180
#define ScreenHeight    640
#define Scale 100
#define Ex -7
#define Ey 30
#define DistanceGrid 0.5f
#define GridColor Color(170,170,170,255)

class Renderer
{
private:
    RenderTarget& m_target;

public:
    explicit
        Renderer(RenderTarget& target) : m_target{ target } {
    }

    void render(Vector2i Pos, Objects Obj) const;
    static Vector2f R2Pos(Vector2f Pos, Vector2i ScreenPos);
    static Vector2f R2Pos(Vector2f Pos, float Radius);
    static Vector2f ScPos(Vector2f Pos, float Radius);
    static Vector2f ScPos(Vector2f Pos, Vector2f Dimensions);
    static Color ColorConvert(RGBA Col);

    void RenderMousePosition(Vector2i Pos) const;
    void RenderGrid() const;
    void RenderAxis() const;
    void RenderCircles(Objects Obj) const;
    void RenderRectangles(Objects Obj) const;
    void RenderFunctions(Objects Obj) const;

};
