#include "Engine.h"
#include <chrono>
#include <thread>

Engine::Engine()
{   
    Values.push_back(DefaultInitialPoints);
    Values.push_back(DefaultPointsFunction);
    Values.push_back(DefaultFourierDepth);
    fourier.push_back(Fourier());
    fourier[0].CreateDataSet(Values[FourierPoints]);
}

void Engine::MainLoop()
{
    RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "Fourier Plotter", Style::Default);
    window.setPosition(InitialWinPos);
    Renderer renderer(window);
    Rend = &renderer;
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        EventCheck(window);
        if (window.hasFocus() && SomethingHasChanged) {
            renderer.renderPlain(window.getPosition());
            for (int i = 0; i < fourier.size(); i++)
                fourier[i].RenderFunction(renderer);
            fourier[currentFourier].RenderPoints(renderer);
            settings.DrawSettings(renderer);
            window.display();
        }
        else {
using namespace std;
            this_thread::sleep_for(30ms);
using namespace sf;
        }
            
    }
}

void Engine::EventCheck(RenderWindow& window)
{
    SomethingHasChanged = false;
    Event event;
    WindowMovement(window.getPosition());
    Vector2f MousePosition = Renderer::R2Pos((Vector2f)Mouse::getPosition(), WindowPosition, Rend->getScale());
    
    // Everrything to do with settings events
    if (fourier[currentFourier].IsDrawing())
        Values[FourierPoints] = fourier[currentFourier].GetNumberPoints();
    settings.SetValues(Values);
    ButtonsActions(settings.SettingsEvents(MouseWindowPosition(), fouriersOccupied(), PressingButton));

    // Everything to do with function events
    if (!PressingButton) {
        for (int i = 0; i < fourier.size(); i++)
            fourier[i].FunctionEvents(SomethingHasChanged, MousePosition, Rend->getScale(), Values);
    }

    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();
        if (event.type == sf::Event::MouseWheelMoved)
        {
            Rend->ModifyScale((float)event.mouseWheel.delta);
            change();
        }   
    }
}

void Engine::KeyboardEventCheck()
{
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        if (!KeyCooldown) {
            Values[FourierDepth]++;
            KeyCooldown = StdKeyCooldown;
            change();
        }
        else KeyCooldown--;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) && Values[FourierDepth] > 2) {
        if (!KeyCooldown) {
            Values[FourierDepth]--;
            KeyCooldown = StdKeyCooldown;
            change();
        }
        else KeyCooldown--;
    }
    else if (Keyboard::isKeyPressed(Keyboard::A) && Values[PointsFunction] > 10) {
        if (!KeyCooldown) {
            Values[PointsFunction] -= 10;
            KeyCooldown = StdKeyCooldown;
            change();
        }
        else KeyCooldown--;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D)) {
        if (!KeyCooldown) {
            Values[PointsFunction] += 10;
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

void Engine::Reset()
{
    Values[FourierPoints] = DefaultInitialPoints;
    Values[PointsFunction] = DefaultPointsFunction;
    Values[FourierDepth] = DefaultFourierDepth;
    fourier[currentFourier].CreateDataSet(Values[FourierPoints]);
}

Vector2i Engine::MouseWindowPosition()
{
    return Vector2i(Mouse::getPosition().x - WindowPosition.x + Ex, Mouse::getPosition().y - WindowPosition.y - Ey);
}

void Engine::WindowMovement(Vector2i NewWindowPosition)
{
    if (WindowPosition != NewWindowPosition) {
        WindowPosition = NewWindowPosition;
        Rend->SetWindowPos(WindowPosition);
        change();
    }
}

void Engine::change()
{
    SomethingHasChanged = true;
}

bool Engine::fouriersOccupied()
{
    for (int i = 0; i < fourier.size(); i++) {
        if (fourier[i].IsOccupied())
            return true;
    }
    return false;
}

void Engine::ButtonsActions(int ButtonPressed)
{
    if (ButtonPressed)
        change();
    if (ButtonPressed == Settings::IncreaseDepth)
        Values[FourierDepth]++;
    else if (ButtonPressed == Settings::DecreaseDepth && Values[FourierDepth] > 2)
        Values[FourierDepth]--;
    else if (ButtonPressed == Settings::IncreaseSmoothness)
        Values[PointsFunction] += 10;
    else if (ButtonPressed == Settings::DecreaseSmoothness && Values[PointsFunction] > 10)
        Values[PointsFunction] -= 10;
    else if (ButtonPressed == Settings::IncreasePoints)
        fourier[currentFourier].AddPointstoDataSet(++Values[FourierPoints]);
    else if (ButtonPressed == Settings::DecreasePoints && Values[FourierPoints] > 3)
        fourier[currentFourier].AddPointstoDataSet(--Values[FourierPoints]);
    else if (ButtonPressed == Settings::Reset)
        Reset();
    else if (ButtonPressed == Settings::Draw)
        fourier[currentFourier].Draw();
}
