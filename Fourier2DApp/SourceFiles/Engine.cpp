#include "Engine.h"

void Engine::MainLoop()
{
    RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "Fourier Plotter", Style::Default);
    window.setPosition(InitialWinPos);
    Renderer renderer(window);
    Rend = &renderer;
    window.setFramerateLimit(60);
    CreateObjects();
    renderer.InitializeTextures();

    while (window.isOpen())
    {
        EventCheck(window);
        AddFunctionS0();
        renderer.render(window.getPosition(), Obj);
        renderer.RenderSettings(SettingsPosition, SettingsOpen, FourierDepth);
        window.display();
    }
}

void Engine::EventCheck(RenderWindow& window)
{
    Event event;
    Vector2f MousePosition = Renderer::R2Pos((Vector2f)Mouse::getPosition(), window.getPosition(), Rend->getScale());
    int Object = CheckCollision(MousePosition);
    if (SettingsOpen && SettingsPosition.x < 0.f)
        SettingsPosition.x += 10;
    if (!SettingsOpen && SettingsPosition.x > -120.f)
        SettingsPosition.x -= 10;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();
        if (Mouse::isButtonPressed(Mouse::Left)){
            if (Dragging == -2);
            else if (Dragging >= 0) {
                Obj.SetCirclePos(Dragging, MousePosition.x, MousePosition.y);
            }
            else {
                if (Object >= 0) {
                    Obj.SetCirclePos(Object, MousePosition.x, MousePosition.y);
                    Dragging = Object;
                }
                else {
                    Dragging = -2;
                    if (!SettingsOpen && isMouseInSquare(0.f,38.f,5.f,33.f,(Vector2f)window.getPosition())) {
                        SettingsOpen = true;
                    }
                    else if (SettingsOpen && isMouseInSquare(120.f, 158.f, 5.f, 33.f, (Vector2f)window.getPosition())) {
                        SettingsOpen = false;
                    }
                }
                    
            }
        }
        else {
            Dragging = -1;
            if (Object >= 0) {
                Obj.SetCircleDescription(Object, true);
            }
            else {
                Obj.SetDescriptionsFalse();
            }
        }
        if (event.type == sf::Event::MouseWheelMoved)
        {
            Rend->ModifyScale((float)event.mouseWheel.delta);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (!KeyCooldown) {
                FourierDepth++;
                KeyCooldown = StdKeyCooldown;
            }
            else KeyCooldown--;
        }
        else if (Keyboard::isKeyPressed(Keyboard::S) && FourierDepth > 2) {
            if (!KeyCooldown) {
                FourierDepth--;
                KeyCooldown = StdKeyCooldown;
            }
            else KeyCooldown--;
        }
        else
            KeyCooldown = 0;
            
    }
}

void Engine::CreateObjects()
{
    float* r = (float*)calloc(sizeof(float), InitialPoints);
    float* x = (float*)calloc(sizeof(float), InitialPoints);
    float* y = (float*)calloc(sizeof(float), InitialPoints);
    RGBA* c = (RGBA*)calloc(sizeof(RGBA), InitialPoints);
    for (int i = 0; i < InitialPoints; i++) {
        r[i] = PointsRadius;
        x[i] = (float)cos(2 * Pi / InitialPoints * i);
        y[i] = (float)sin(2 * Pi / InitialPoints * i);
        c[i] = PointsColor;
    }
    Obj.InitializeCircles(InitialPoints, r, x, y, c);
    Obj.InitializeButtons(0, r, r, x, y, c);
}

int Engine::CheckCollision(Vector2f mouse)
{
    for (int i = 0; i < Obj.NumOfCircles; i++) {
        if (Distance2(mouse, Obj.GetCirclePos(i)) < (Obj.GetCircleRadius(i) / Rend->getScale()) * (Obj.GetCircleRadius(i) / Rend->getScale()))
            return i;
    }
    return -1;
}

float Engine::Distance2(Vector2f V0, Vector2f V1)
{
    return (V1.x - V0.x) * (V1.x - V0.x) + (V1.y - V0.y) * (V1.y - V0.y);
}

void Engine::AddFunctionS0()
{
    Fourier fourier;
    fourier.initialize();
    fourier.CreateDataSet(Obj);
    fourier.SetDepth(FourierDepth);
    fourier.GenerateS0();
    dataset Graph = fourier.FourierS0DataSet(PointsFunction);
    float* x = (float*)calloc(sizeof(float), PointsFunction);
    float* y = (float*)calloc(sizeof(float), PointsFunction);
    RGBA* c = (RGBA*)calloc(sizeof(RGBA), PointsFunction);

    for (int i = 0; i < PointsFunction; i++) {
        x[i] = (float)Graph.X[i];
        y[i] = (float)Graph.Y[i];
        c[i] = RGBA('R');
    }
    if (Obj.NumOfFunctions == 0)
        Obj.AddFunction(PointsFunction, x, y, c);
    else
        Obj.ModifyFunction(0, PointsFunction, x, y, c);
}

bool Engine::isMouseInSquare(float x0, float x1, float y0, float y1, Vector2f ScreenPos)
{
    float X = (float)Mouse::getPosition().x - ScreenPos.x + Ex;
    float Y = (float)Mouse::getPosition().y - ScreenPos.y - Ey;
    if (X >= x0 && X <= x1 && Y >= y0 && Y <= y1)
        return true;
    return false;
}
