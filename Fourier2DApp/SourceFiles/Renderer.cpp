#include "Renderer.h"

Renderer::Renderer(RenderTarget& target) : m_target{ target }
{
    font.loadFromFile(ArialFontFile);
}

void Renderer::SetWindowPos(Vector2i WinPos)
{
    WindowPos = WinPos;
}

void Renderer::renderPlain(Vector2i Pos) const
{
    RenderAxis();
    RenderGrid();
}

void Renderer::ModifyScale(float increment)
{
    Scale = Scale * (float)pow(1.05, increment);
    if (Scale < MinScale) {
        Scale = MinScale;
    }
    if (Scale > MaxScale) {
        Scale = MaxScale;
    }
}

float Renderer::getScale()
{
    return Scale;
}

Vector2f Renderer::R2Pos(Vector2f Pos, Vector2i ScreenPos, float scale)
{
    Vector2f Vec;
    Vec.x = (float)Pos.x - (float)ScreenPos.x - (float)ScreenWidth / 2 + Ex;
    Vec.y = (float)ScreenHeight / 2 - (float)Pos.y + (float)ScreenPos.y + Ey;
    Vec.x = Vec.x / scale;
    Vec.y = Vec.y / scale;
    return Vec;
}

Vector2f Renderer::R2Pos(Vector2f Pos, float Radius, float scale)
{
    Vector2f Vec;
    Vec.x = (float)Pos.x - (float)ScreenWidth / 2 + Radius;
    Vec.y = (float)ScreenHeight / 2 - (float)Pos.y - Radius;
    Vec.x = Vec.x / scale;
    Vec.y = Vec.y / scale;
    return Vec;
}

Vector2f Renderer::ScPos(Vector2f Pos, float Radius, float scale)
{
    Vector2f Vec;
    Vec.x = Pos.x * scale - Radius + ScreenWidth / 2;
    Vec.y = - Pos.y * scale - Radius + ScreenHeight / 2;
    return Vec;
}

Vector2f Renderer::ScPos(Vector2f Pos, Vector2f Dimensions, float scale)
{
    Vector2f Vec;
    Vec.x = Pos.x * scale - Dimensions.x / 2 + ScreenWidth / 2;
    Vec.y = -Pos.y * scale - Dimensions.y / 2 + ScreenHeight / 2;
    return Vec;
}

void Renderer::RenderMousePosition(Vector2i Pos) const
{
    RectangleShape Back(Vector2f(157.f, 14.f));
    Back.setPosition(Vector2f(0.f, ScreenHeight - 14.f));
    Back.setFillColor(Color(210, 210, 210, 255));
    m_target.draw(Back);

    Vector2f mpR2 = R2Pos((Vector2f)Mouse::getPosition(), Pos, Scale);
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
    Vector2f Origin = R2Pos(Vector2f(0.f, 0.f), 0.f, Scale);
    for (int i = 1; i < -Origin.x / DistanceGrid; i++) {
        Vertex t0(ScPos(Vector2f(DistanceGrid * i, Origin.y), 0.f, Scale));
        Vertex t1(ScPos(Vector2f(DistanceGrid * i, -Origin.y), 0.f, Scale));
        t0.color = GridColor;
        t1.color = GridColor;
        Vertex Yaxis[] = { t0,t1 };
        m_target.draw(Yaxis, 2, Lines);
    }
    for (int i = 1; i < -Origin.x / DistanceGrid; i++) {
        Vertex t0(ScPos(Vector2f(-DistanceGrid * i, Origin.y), 0.f, Scale));
        Vertex t1(ScPos(Vector2f(-DistanceGrid * i, -Origin.y), 0.f, Scale));
        t0.color = GridColor;
        t1.color = GridColor;
        Vertex Yaxis[] = { t0,t1 };
        m_target.draw(Yaxis, 2, Lines);
    }
    for (int i = 1; i < Origin.y / DistanceGrid; i++) {
        Vertex t0(ScPos(Vector2f(Origin.x, DistanceGrid * i), 0.f, Scale));
        Vertex t1(ScPos(Vector2f(-Origin.x, DistanceGrid * i), 0.f, Scale));
        t0.color = GridColor;
        t1.color = GridColor;
        Vertex Yaxis[] = { t0,t1 };
        m_target.draw(Yaxis, 2, Lines);
    }
    for (int i = 1; i < Origin.y / DistanceGrid; i++) {
        Vertex t0(ScPos(Vector2f(Origin.x, -DistanceGrid * i), 0.f, Scale));
        Vertex t1(ScPos(Vector2f(-Origin.x, -DistanceGrid * i), 0.f, Scale));
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

void Renderer::RenderPoint(Point P, int i) const
{
    if (P.Description)
        RenderCircleDescription(P, i);
    CircleShape Circle;
    Circle.setPosition(ScPos(P.Position, P.Radius, Scale));
    Circle.setRadius(P.Radius);
    Circle.setFillColor(P.color);
    m_target.draw(Circle);
}

void Renderer::RenderFunction(PixelFunction& Function) const
{
    for (int i = 0; i < Function.N - 1; i++) {
        Vertex t0 = ScPos(Vector2f(Function.x[i], Function.y[i]), 0, Scale);
        Vertex t1 = ScPos(Vector2f(Function.x[i + 1], Function.y[i + 1]), 0, Scale);
        t0.color = Function.color[i];
        t1.color = Function.color[i + 1];
        Vertex line[] = { t0,t1 };
        m_target.draw(line, 2, Lines);
    }
}

void Renderer::RenderCircleDescription(Point P, int n) const
{
    CircleShape     Circle;
    Vector2f        Pos = P.Position;
    float           Rad = P.Radius;

    Circle.setRadius(Rad + 3);
    Circle.setPosition(ScPos(Pos, Rad + 3, Scale));
    Circle.setFillColor(Color(180,180,180,255));
    m_target.draw(Circle);

    std::string String = 'P' + std::to_string(n + 1) + '(' + 
            std::to_string(Pos.x).erase(std::to_string(Pos.x).length() - 4) + ',' +
            std::to_string(Pos.y).erase(std::to_string(Pos.y).length() - 4) + ')';
    Text text;
    Font font;
    font.loadFromFile("Resources/Fonts/arial.ttf");
    text.setString(String);
    text.setCharacterSize(12);
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setPosition((float)Mouse::getPosition().x - (float)WindowPos.x, (float)Mouse::getPosition().y - (float)WindowPos.y - 40.f);
    m_target.draw(text);

}

void Renderer::RenderSprite(Sprite& sprite) const
{
    m_target.draw(sprite);
}

void Renderer::RenderTexts(std::vector<Text> Texts)
{
    int N = Texts.size();
    for (int i = 0; i < N; i++)
        m_target.draw(Texts[i]);
}

void Renderer::RenderText(Text text)
{
    text.setFont(font);
    m_target.draw(text);
}
