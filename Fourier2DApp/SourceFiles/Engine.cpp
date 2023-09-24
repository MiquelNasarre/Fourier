#include "Engine.h"

void Engine::MainLoop()
{
    RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "Fourier Plotter", Style::Default);
    window.setPosition(InitialWinPos);
    Renderer renderer(window);
    window.setFramerateLimit(60);
    CreateObjects();

    while (window.isOpen())
    {
        EventCheck(window);
        AddFunctionS0();
        renderer.render(window.getPosition(), Obj);
        window.display();
    }
}

void Engine::EventCheck(RenderWindow& window)
{
    Event event;
    Vector2f MousePosition = Renderer::R2Pos((Vector2f)Mouse::getPosition(), window.getPosition());
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();
        if (Keyboard::isKeyPressed(Keyboard::W))
            Obj.SetCirclePos(0, Obj.GetCirclePos(0).x + 0.01f, Obj.GetCirclePos(0).y);
        if (Mouse::isButtonPressed(Mouse::Left)){
            Vector2f mouse = Renderer::R2Pos((Vector2f)Mouse::getPosition(), window.getPosition());
            if (Dragging == -2);
            else if (Dragging >= 0) {
                Obj.SetCirclePos(Dragging, mouse.x, mouse.y);
            }
            else {
                int Object = CheckCollision(mouse);
                if (Object >= 0) {
                    Obj.SetCirclePos(Object, mouse.x, mouse.y);
                    Dragging = Object;
                }
                else
                    Dragging = -2;
            }
        }
        else {
            Dragging = -1;
        }
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
    Obj.InitializeRectangles(0, r, r, x, y, c);
}

int Engine::CheckCollision(Vector2f mouse)
{
    for (int i = 0; i < Obj.NumOfCircles; i++) {
        if (Distance2(mouse, Obj.GetCirclePos(i)) < (Obj.GetCircleRadius(i) / Scale) * (Obj.GetCircleRadius(i) / Scale))
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
    fourier.SetDepth(10);
    fourier.GenerateS0();
    dataset Graph = fourier.FourierS0DataSet(PointsFunction);
    float* x = (float*)calloc(sizeof(float), PointsFunction);
    float* y = (float*)calloc(sizeof(float), PointsFunction);
    RGBA* c = (RGBA*)calloc(sizeof(RGBA), PointsFunction);

    for (int i = 0; i < PointsFunction; i++) {
        x[i] = (float)Graph.X[i];
        y[i] = (float)Graph.Y[i];
        //printf("(%f,%f)", (float)Graph.X[i], (float)Graph.Y[i]);
        c[i] = RGBA('R');
    }
    if (Obj.NumOfFunctions == 0)
        Obj.AddFunction(PointsFunction, x, y, c);
    else
        Obj.ModifyFunction(0, PointsFunction, x, y, c);
}
