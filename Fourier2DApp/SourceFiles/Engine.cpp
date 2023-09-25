#include "Engine.h"
#include <chrono>
#include <thread>

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
        if (window.hasFocus() && SomethingHasChanged) {
            AddFunctionS0();
            renderer.render(window.getPosition(), Obj);
            renderer.RenderSettings(SettingsPosition, SettingsOpen, FourierDepth, PointsFunction, InitialPoints, Obj);
            window.display();
        }
        else
            std::this_thread::sleep_for(30ms);
    }
}

void Engine::EventCheck(RenderWindow& window)
{
    SomethingHasChanged = false;
    Event event;
    WindowMovement(window.getPosition());
    Vector2f MousePosition = Renderer::R2Pos((Vector2f)Mouse::getPosition(), WindowPosition, Rend->getScale());
    
    PreEventModifiers();
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        MouseEvents(MousePosition);
        settingsEventCheck();
        ButtonsState();

        if (event.type == sf::Event::MouseWheelMoved)
        {
            Rend->ModifyScale((float)event.mouseWheel.delta);
            change();
        }   
    }
}

void Engine::settingsEventCheck()
{
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        if (!KeyCooldown) {
            FourierDepth++;
            KeyCooldown = StdKeyCooldown;
            change();
        }
        else KeyCooldown--;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) && FourierDepth > 2) {
        if (!KeyCooldown) {
            FourierDepth--;
            KeyCooldown = StdKeyCooldown;
            change();
        }
        else KeyCooldown--;
    }
    else if (Keyboard::isKeyPressed(Keyboard::A) && PointsFunction > 10) {
        if (!KeyCooldown) {
            PointsFunction -= 10;
            KeyCooldown = StdKeyCooldown;
            change();
        }
        else KeyCooldown--;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D)) {
        if (!KeyCooldown) {
            PointsFunction += 10;
            KeyCooldown = StdKeyCooldown;
            change();
        }
        else KeyCooldown--;
    }
    else if (Keyboard::isKeyPressed(Keyboard::R)) {
        if (!KeyCooldown) {
            Reset();
            KeyCooldown = StdKeyCooldown;
            change();
        }
        else KeyCooldown--;
    }
    else
        KeyCooldown = 0;
}

void Engine::MouseEvents(Vector2f MousePosition)
{
    int Object = CheckCollision(MousePosition);
    if (Mouse::isButtonPressed(Mouse::Left)) {
        if (Dragging == -2);
        else if (Dragging >= 0) {
            Obj.SetCirclePos(Dragging, MousePosition.x, MousePosition.y);
            change();
        }
        else {
            if (Object >= 0) {
                Obj.SetCirclePos(Object, MousePosition.x, MousePosition.y);
                Dragging = Object;
                change();
            }
            else {
                Dragging = -2;
                if (!SettingsOpen && isMouseInSquare(0.f, 38.f, 5.f, 33.f)) {
                    SettingsOpen = true;
                    Obj.getButton(IncreaseDepthButton)->ToBe = true;
                    Obj.getButton(DecreaseDepthButton)->ToBe = true;
                    Obj.getButton(IncreaseSmoothnessButton)->ToBe = true;
                    Obj.getButton(DecreaseSmoothnessButton)->ToBe = true;
                    Obj.getButton(IncreasePointsButton)->ToBe = true;
                    Obj.getButton(DecreasePointsButton)->ToBe = true;
                    Obj.getButton(ResetButton)->ToBe = true;
                    Obj.getButton(DrawButton)->ToBe = true;
                }
                else if (SettingsOpen && isMouseInSquare(120.f, 158.f, 5.f, 33.f)) {
                    SettingsOpen = false;
                    Obj.getButton(IncreaseDepthButton)->ToBe = false;
                    Obj.getButton(DecreaseDepthButton)->ToBe = false;
                    Obj.getButton(IncreaseSmoothnessButton)->ToBe = false;
                    Obj.getButton(DecreaseSmoothnessButton)->ToBe = false;
                    Obj.getButton(IncreasePointsButton)->ToBe = false;
                    Obj.getButton(DecreasePointsButton)->ToBe = false;
                    Obj.getButton(ResetButton)->ToBe = false;
                    Obj.getButton(DrawButton)->ToBe = false;
                }
            }

        }
    }
    else {
        Dragging = -1;
        if (Object >= 0) {
            Obj.SetCircleDescription(Object, true);
            ObjectDescription = true;
            change();
        }
        else if (ObjectDescription) {
            Obj.SetDescriptionsFalse();
            change();
        }
    }
}

void Engine::PreEventModifiers()
{
    ButtonsActions();
    if (SettingsOpen && SettingsPosition.x < 0.f) {
        SettingsPosition.x += 20;
        Obj.getButton(IncreaseDepthButton)->IncreasePosition(20.f, 0);
        Obj.getButton(DecreaseDepthButton)->IncreasePosition(20.f, 0);
        Obj.getButton(IncreaseSmoothnessButton)->IncreasePosition(20.f, 0);
        Obj.getButton(DecreaseSmoothnessButton)->IncreasePosition(20.f, 0);
        Obj.getButton(IncreasePointsButton)->IncreasePosition(20.f, 0);
        Obj.getButton(DecreasePointsButton)->IncreasePosition(20.f, 0);
        Obj.getButton(ResetButton)->IncreasePosition(20.f, 0);
        Obj.getButton(DrawButton)->IncreasePosition(20.f, 0);


        change();
    }
        
    if (!SettingsOpen && SettingsPosition.x > -120.f) {
        SettingsPosition.x -= 15;
        Obj.getButton(IncreaseDepthButton)->IncreasePosition(-15.f, 0);
        Obj.getButton(DecreaseDepthButton)->IncreasePosition(-15.f, 0);
        Obj.getButton(IncreaseSmoothnessButton)->IncreasePosition(-15.f, 0);
        Obj.getButton(DecreaseSmoothnessButton)->IncreasePosition(-15.f, 0);
        Obj.getButton(IncreasePointsButton)->IncreasePosition(-15.f, 0);
        Obj.getButton(DecreasePointsButton)->IncreasePosition(-15.f, 0);
        Obj.getButton(ResetButton)->IncreasePosition(-15.f, 0);
        Obj.getButton(DrawButton)->IncreasePosition(-15.f, 0);
        change();
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
    Obj.InitializeButtons();
}

void Engine::Reset()
{
    InitialPoints = DefaultInitialPoints;
    PointsFunction = DefaultPointsFunction;
    FourierDepth = DefaultFourierDepth;
    CreateObjects();
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

bool Engine::isMouseInSquare(float x0, float x1, float y0, float y1)
{
    float X = (float)Mouse::getPosition().x - (float)WindowPosition.x + Ex;
    float Y = (float)Mouse::getPosition().y - (float)WindowPosition.y - Ey;
    if (X > x0 && X <= x1 && Y > y0 && Y <= y1)
        return true;
    return false;
}

void Engine::WindowMovement(Vector2i NewWindowPosition)
{
    if (WindowPosition != NewWindowPosition) {
        WindowPosition = NewWindowPosition;
        change();
    }
}

void Engine::change()
{
    SomethingHasChanged = true;
}

void Engine::ButtonsState()
{
    for (int i = 0; i < Obj.NumOfButtons; i++) {
        Button* button = Obj.getButton(i);
        if (!button->ToBe)
            continue;
        if (isMouseInSquare(button->Position.x, button->Position.x + button->Dimensions.x, button->Position.y, button->Position.y + button->Dimensions.y)) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (button->State != 2) {
                    button->State = 2;
                    change();
                }
            }
            else if (button->State != 1) {
                button->State = 1;
                change();
            }
        }
        else if (button->State != 0) {
            button->State = 0;
            change();
        }
    }
}

void Engine::ButtonsActions()
{
    if (ButtonPressed(IncreaseDepthButton)) {
        if (!ButtonCooldown) {
            FourierDepth++;
            ButtonCooldown = StdButtonCooldown;
            change();
        }
        else ButtonCooldown--;
    }
    else if (ButtonPressed(DecreaseDepthButton)) {
        if (!ButtonCooldown && FourierDepth > 2) {
            FourierDepth--;
            ButtonCooldown = StdButtonCooldown;
            change();
        }
        else ButtonCooldown--;
    }
    else if (ButtonPressed(IncreaseSmoothnessButton)) {
        if (!ButtonCooldown) {
            PointsFunction += 10;
            ButtonCooldown = StdButtonCooldown;
            change();
        }
        else ButtonCooldown--;
    }
    else if (ButtonPressed(DecreaseSmoothnessButton)) {
        if (!ButtonCooldown && PointsFunction > 10) {
            PointsFunction -= 10;
            ButtonCooldown = StdButtonCooldown;
            change();
        }
        else ButtonCooldown--;
    }
    else if (ButtonPressed(IncreasePointsButton)) {
        if (!ButtonCooldown) {
            InitialPoints ++;
            fourier.AddPointstoDataSet(InitialPoints);
            float* r = (float*)calloc(sizeof(float), InitialPoints);
            float* x = (float*)calloc(sizeof(float), InitialPoints);
            float* y = (float*)calloc(sizeof(float), InitialPoints);
            RGBA* c = (RGBA*)calloc(sizeof(RGBA), InitialPoints);
            for (int i = 0; i < InitialPoints; i++) {
                r[i] = PointsRadius;
                x[i] = (float)fourier.D->X[i];
                y[i] = (float)fourier.D->Y[i];
                c[i] = PointsColor;
            }
            Obj.InitializeCircles(InitialPoints, r, x, y, c);
            ButtonCooldown = StdButtonCooldown;
            change();
        }
        else ButtonCooldown--;
    }
    else if (ButtonPressed(DecreasePointsButton)) {
        if (!ButtonCooldown && InitialPoints > 3) {
            InitialPoints--;
            fourier.AddPointstoDataSet(InitialPoints);
            float* r = (float*)calloc(sizeof(float), InitialPoints);
            float* x = (float*)calloc(sizeof(float), InitialPoints);
            float* y = (float*)calloc(sizeof(float), InitialPoints);
            RGBA* c = (RGBA*)calloc(sizeof(RGBA), InitialPoints);
            for (int i = 0; i < InitialPoints; i++) {
                r[i] = PointsRadius;
                x[i] = (float)fourier.D->X[i];
                y[i] = (float)fourier.D->Y[i];
                c[i] = PointsColor;
            }
            Obj.InitializeCircles(InitialPoints, r, x, y, c);
            ButtonCooldown = StdButtonCooldown;
            change();
        }
        else ButtonCooldown--;
    }
    else if (ButtonPressed(ResetButton)) {
        if (!ButtonCooldown) {
            Reset();
            ButtonCooldown = StdButtonCooldown;
            change();
        }
        else ButtonCooldown--;
    }
    else
        ButtonCooldown = 0;
}

bool Engine::ButtonPressed(int i)
{
    if (Obj.getButton(i)->State == 2)
        return true;
    return false;
}