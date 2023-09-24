#include "Renderer.h"

void Renderer::render(Vector2i Pos, Objects Obj) const
{
    m_target.clear(Color::White);

    RenderAxis();
    RenderGrid();
    RenderFunctions(Obj);
    RenderCircles(Obj);
    RenderRectangles(Obj);
    RenderMousePosition(Pos);
}

Vector2f Renderer::R2Pos(Vector2f Pos, Vector2i ScreenPos)
{
    Vector2f Vec;
    Vec.x = (float)Pos.x - (float)ScreenPos.x - (float)ScreenWidth / 2 + Ex;
    Vec.y = (float)ScreenHeight / 2 - (float)Pos.y + (float)ScreenPos.y + Ey;
    Vec.x = Vec.x / Scale;
    Vec.y = Vec.y / Scale;
    return Vec;
}

Vector2f Renderer::R2Pos(Vector2f Pos, float Radius)
{
    Vector2f Vec;
    Vec.x = (float)Pos.x - (float)ScreenWidth / 2 + Radius;
    Vec.y = (float)ScreenHeight / 2 - (float)Pos.y - Radius;
    Vec.x = Vec.x / Scale;
    Vec.y = Vec.y / Scale;
    return Vec;
}

Vector2f Renderer::ScPos(Vector2f Pos, float Radius)
{
    Vector2f Vec;
    Vec.x = Pos.x * Scale - Radius + ScreenWidth / 2;
    Vec.y = - Pos.y * Scale - Radius + ScreenHeight / 2;
    return Vec;
}

Vector2f Renderer::ScPos(Vector2f Pos, Vector2f Dimensions)
{
    Vector2f Vec;
    Vec.x = Pos.x * Scale - Dimensions.x / 2 + ScreenWidth / 2;
    Vec.y = -Pos.y * Scale - Dimensions.y / 2 + ScreenHeight / 2;
    return Vec;
}

Color Renderer::ColorConvert(RGBA Col)
{
    return Color(Col.R, Col.G, Col.B, Col.A);
}

void Renderer::RenderMousePosition(Vector2i Pos) const
{
    RectangleShape Back(Vector2f(157.f, 14.f));
    Back.setPosition(Vector2f(0.f, ScreenHeight - 14.f));
    Back.setFillColor(Color(210, 210, 210, 255));
    m_target.draw(Back);

    Vector2f mpR2 = R2Pos((Vector2f)Mouse::getPosition(), Pos);
    int Eraserx = 4, Erasery = 4;
    if (mpR2.x < 0)Eraserx++;
    if (mpR2.y < 0)Erasery++;
    std::string String = "Mouse position:  " + std::to_string(mpR2.x).erase(Eraserx, Eraserx + 1)
        + " , " + std::to_string(mpR2.y).erase(Erasery, Erasery + 1);
    Text text;
    Font font;
    font.loadFromFile("Resources/Fonts/arial.ttf");
    text.setString(String);
    text.setCharacterSize(12);
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setPosition(2.f, ScreenHeight - 15.f);
    m_target.draw(text);
}

void Renderer::RenderGrid() const
{
    Vector2f Origin = R2Pos(Vector2f(0.f, 0.f), 0.f);
    for (int i = 1; i < -Origin.x / DistanceGrid; i++) {
        Vertex t0(ScPos(Vector2f(DistanceGrid * i, Origin.y), 0.f));
        Vertex t1(ScPos(Vector2f(DistanceGrid * i, -Origin.y), 0.f));
        t0.color = GridColor;
        t1.color = GridColor;
        Vertex Yaxis[] = { t0,t1 };
        m_target.draw(Yaxis, 2, Lines);
    }
    for (int i = 1; i < -Origin.x / DistanceGrid; i++) {
        Vertex t0(ScPos(Vector2f(-DistanceGrid * i, Origin.y), 0.f));
        Vertex t1(ScPos(Vector2f(-DistanceGrid * i, -Origin.y), 0.f));
        t0.color = GridColor;
        t1.color = GridColor;
        Vertex Yaxis[] = { t0,t1 };
        m_target.draw(Yaxis, 2, Lines);
    }
    for (int i = 1; i < Origin.y / DistanceGrid; i++) {
        Vertex t0(ScPos(Vector2f(Origin.x, DistanceGrid * i), 0.f));
        Vertex t1(ScPos(Vector2f(-Origin.x, DistanceGrid * i), 0.f));
        t0.color = GridColor;
        t1.color = GridColor;
        Vertex Yaxis[] = { t0,t1 };
        m_target.draw(Yaxis, 2, Lines);
    }
    for (int i = 1; i < Origin.y / DistanceGrid; i++) {
        Vertex t0(ScPos(Vector2f(Origin.x, -DistanceGrid * i), 0.f));
        Vertex t1(ScPos(Vector2f(-Origin.x, -DistanceGrid * i), 0.f));
        t0.color = GridColor;
        t1.color = GridColor;
        Vertex Yaxis[] = { t0,t1 };
        m_target.draw(Yaxis, 2, Lines);
    }
}

void Renderer::RenderAxis() const
{
    Vertex t0(Vector2f((float)ScreenWidth / 2, 0.f));
    t0.color = Color::Black;
    Vertex t1(Vector2f((float)ScreenWidth / 2, (float)ScreenHeight));
    t1.color = Color::Black;
    Vertex Yaxis[] = { t0,t1 };
    m_target.draw(Yaxis, 2, Lines);

    t0.position = Vector2f(0.f, (float)ScreenHeight / 2);
    t1.position = Vector2f((float)ScreenWidth, (float)ScreenHeight / 2);
    Vertex Xaxis[] = { t0,t1 };
    m_target.draw(Xaxis, 2, Lines);
}

void Renderer::RenderCircles(Objects Obj) const
{
    CircleShape     Circle;
    Vector2f        Pos;
    float           Rad;
    RGBA            Col;

    for (int i = 0; i < Obj.NumOfCircles; i++) {
        Pos = Obj.GetCirclePos(i);
        Rad = Obj.GetCircleRadius(i);
        Col = Obj.GetCircleColor(i);

        Circle.setRadius(Rad);
        Circle.setPosition(ScPos(Pos, Rad));
        Circle.setFillColor(ColorConvert(Col));
        m_target.draw(Circle);
    }
}

void Renderer::RenderRectangles(Objects Obj) const
{
    RectangleShape  Rectangle;
    Vector2f        Pos, Dim;
    RGBA            Col;

    for (int i = 0; i < Obj.NumOfRectangles; i++) {
        Pos = Obj.GetRectanglePos(i);
        Dim = Obj.GetRectangleDimensions(i);
        Col = Obj.GetRectangleColor(i);

        Rectangle.setSize(Dim);
        Rectangle.setPosition(ScPos(Pos, Dim));
        Rectangle.setFillColor(ColorConvert(Col));
        m_target.draw(Rectangle);
    }
}

void Renderer::RenderFunctions(Objects Obj) const
{
    for (int n = 0; n < Obj.NumOfFunctions; n++) {
        PixelFunction* Function = Obj.GetFunction(n);
        for (int i = 0; i < Function->N - 1; i++) {
            Vertex t0 = ScPos(Vector2f(Function->x[i], Function->y[i]), 0);
            Vertex t1 = ScPos(Vector2f(Function->x[i + 1], Function->y[i + 1]), 0);
            t0.color = ColorConvert(Function->Color[i]);
            t1.color = ColorConvert(Function->Color[i+1]);
            Vertex line[] = { t0,t1 };
            m_target.draw(line, 2, Lines);
        }
    }
}
