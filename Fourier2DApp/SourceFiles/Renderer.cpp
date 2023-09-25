#include "Renderer.h"

void Renderer::InitializeTextures()
{
    Image   image;
    Texture ButtonTex;
    Sprite  Button;

    image.loadFromFile("Resources/Textures/CustomButtons.png");
    Objects::TransparentGreenScreen(&image);
    ButtonTex.loadFromImage(image, IntRect(0, 104, 157, 352));
    Textures.push_back(ButtonTex);
    ButtonTex.loadFromImage(image, IntRect(157, 104, 157, 352));
    Textures.push_back(ButtonTex);
    Button.setTexture(Textures[0]);
    Button.setScale(1.f, 1.f);
    Sprites.push_back(Button);
}

void Renderer::render(Vector2i Pos, Objects Obj) const
{
    m_target.clear(Color::White);

    RenderAxis();
    RenderGrid();
    RenderFunctions(Obj);
    RenderCircles(Obj,Pos);
    RenderMousePosition(Pos);
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

void Renderer::RenderCircles(Objects Obj, Vector2i ScreenPos) const
{
    CircleShape     Circle;
    Vector2f        Pos;
    float           Rad;
    RGBA            Col;
    
    for (int i = 0; i < Obj.NumOfCircles; i++) {
        if (Obj.GetCircleDescription(i))
            RenderCircleDescription(Obj, i, ScreenPos);
        Pos = Obj.GetCirclePos(i);
        Rad = Obj.GetCircleRadius(i);
        Col = Obj.GetCircleColor(i);

        Circle.setRadius(Rad);
        Circle.setPosition(ScPos(Pos, Rad, Scale));
        Circle.setFillColor(ColorConvert(Col));
        m_target.draw(Circle);
    }
}

void Renderer::RenderButtons(Objects Obj) const
{
    for (int i = 0; i < Obj.NumOfButtons; i++)
        RenderButton(Obj.getButton(i));
}

void Renderer::RenderFunctions(Objects Obj) const
{
    for (int n = 0; n < Obj.NumOfFunctions; n++) {
        PixelFunction* Function = Obj.GetFunction(n);
        for (int i = 0; i < Function->N - 1; i++) {
            Vertex t0 = ScPos(Vector2f(Function->x[i], Function->y[i]), 0, Scale);
            Vertex t1 = ScPos(Vector2f(Function->x[i + 1], Function->y[i + 1]), 0, Scale);
            t0.color = ColorConvert(Function->Color[i]);
            t1.color = ColorConvert(Function->Color[i+1]);
            Vertex line[] = { t0,t1 };
            m_target.draw(line, 2, Lines);
        }
    }
}

void Renderer::RenderCircleDescription(Objects Obj, int n, Vector2i ScreenPos) const
{
    CircleShape     Circle;
    Vector2f        Pos = Obj.GetCirclePos(n);
    float           Rad = Obj.GetCircleRadius(n);

    Circle.setRadius(Rad + 3);
    Circle.setPosition(ScPos(Pos, Rad + 3, Scale));
    Circle.setFillColor(Color(180,180,180,255));
    m_target.draw(Circle);

    std::string String = 'P' + std::to_string(n + 1) + '(' + 
            std::to_string(Obj.GetCirclePos(n).x).erase(std::to_string(Obj.GetCirclePos(n).x).length() - 4) + ',' +
            std::to_string(Obj.GetCirclePos(n).y).erase(std::to_string(Obj.GetCirclePos(n).y).length() - 4) + ')';
    Text text;
    Font font;
    font.loadFromFile("Resources/Fonts/arial.ttf");
    text.setString(String);
    text.setCharacterSize(12);
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setPosition((float)Mouse::getPosition().x - (float)ScreenPos.x, (float)Mouse::getPosition().y - (float)ScreenPos.y - 40.f);
    m_target.draw(text);

}

void Renderer::RenderSettings(Vector2f Pos, bool State, int depth, int smoothness, int points, Objects Obj)
{
    Sprites[0].setPosition(Pos);
    if (!State) {
        if (OpenSettingsTexture) {
            Sprites[0].setTexture(Textures[1]);
            OpenSettingsTexture = false;
        }
        m_target.draw(Sprites[0]);
    }
    else {
        if (!OpenSettingsTexture) {
            Sprites[0].setTexture(Textures[0]);
            OpenSettingsTexture = true;
        }
        
        std::string String = "Fourier Depth:  " + std::to_string(depth) + 
            "\n\nSmoothness:  " + std::to_string(smoothness) + "\n\nPoints:\t\t       " + 
            std::to_string(points) + "\n\n     Reset\t\t\t   Draw";
        Text text;
        Font font;
        font.loadFromFile("Resources/Fonts/arial.ttf");
        text.setString(String);
        text.setCharacterSize(12);
        text.setFont(font);
        text.setFillColor(Color::Black);
        text.setPosition(Pos.x + 10.f, Pos.y + 35.f);
        m_target.draw(Sprites[0]);
        RenderButtons(Obj);
        m_target.draw(text);
    }
}

void Renderer::RenderButton(Button* button) const
{   
    if (button->ToBe) {
        button->sprite.setTexture(button->Textures[button->State]);
        m_target.draw(button->sprite);
    }
}

