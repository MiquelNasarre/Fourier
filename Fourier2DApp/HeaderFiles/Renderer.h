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
    RenderTarget&           m_target;
    std::vector<Texture>    Textures;
    std::vector<Sprite>     Sprites;
    float Scale = 200;
    bool OpenSettingsTexture = true;

public:
    explicit
        Renderer(RenderTarget& target) : m_target{ target } {
    }

    void InitializeTextures();
    void render(Vector2i Pos, Objects Obj) const;
    void ModifyScale(float increment);
    float getScale();
    static Vector2f R2Pos(Vector2f Pos, Vector2i ScreenPos, float scale);
    static Vector2f R2Pos(Vector2f Pos, float Radius, float scale);
    static Vector2f ScPos(Vector2f Pos, float Radius, float scale);
    static Vector2f ScPos(Vector2f Pos, Vector2f Dimensions, float scale);
    static Color ColorConvert(RGBA Col);

    void RenderMousePosition(Vector2i Pos) const;
    void RenderGrid() const;
    void RenderAxis() const;
    void RenderCircles(Objects Obj, Vector2i Pos) const;
    void RenderButtons(Objects Obj) const;
    void RenderFunctions(Objects Obj) const;
    void RenderCircleDescription(Objects Obj, int n, Vector2i Pos) const;
    void RenderSettings(Vector2f Pos, bool State, int depth, int smoothness, int points, Objects Obj);
    void RenderButton(Button* button) const;
};
