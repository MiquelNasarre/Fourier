#include "Engine.h"

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
            for (int i = 0; i < (int)fourier.size(); i++)
                fourier[i].RenderFunction(renderer);
            if (currentFourier != -1)
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
    if (Keyboard::isKeyPressed(Keyboard::P))
        settings.Selectors[0].SetOptionName(Popup::InputString());
    SomethingHasChanged = false;
    Event event;
    WindowMovement(window.getPosition());
    Vector2f MousePosition = Renderer::R2Pos((Vector2f)Mouse::getPosition(), WindowPosition, Rend->getScale());
    
    // Everrything to do with settings events
    if (currentFourier!=-1 && fourier[currentFourier].IsDrawing())
        Values[FourierPoints] = fourier[currentFourier].GetNumberPoints();
    settings.SetValues(Values);
    ButtonsActions(settings.SettingsEvents(MouseWindowPosition(), fouriersOccupied(), PressingButton));

    // Everything to do with function events
    if (!PressingButton && currentFourier != -1)
        fourier[currentFourier].FunctionEvents(SomethingHasChanged, MousePosition, Rend->getScale(), Values);

    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
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
    if (currentFourier == -1)
        return;
    Values[FourierPoints] = DefaultInitialPoints;
    Values[PointsFunction] = DefaultPointsFunction;
    Values[FourierDepth] = DefaultFourierDepth;
    fourier[currentFourier].CreateDataSet(Values[FourierPoints], InitialRadius);
}

void Engine::AddFourier()
{
    TotalFouriersHad++;
    fourier.push_back(Fourier());
    currentFourier = fourier.size() - 1;
    fourier[currentFourier].CreateDataSet(DefaultInitialPoints, InitialRadius);
    Values.clear();
    Values.push_back(DefaultInitialPoints);
    Values.push_back(DefaultPointsFunction);
    Values.push_back(DefaultFourierDepth);
    PressingButton = false;
    std::string String = "Untitled " + std::to_string(TotalFouriersHad);
    settings.AddToSelector(String);
}

void Engine::DeleteFourier()
{
    if (currentFourier == -1)
        return;
    settings.DeleteSelected();
    fourier.erase(fourier.begin() + currentFourier);
    if (fourier.size()) {
        if (currentFourier)
            currentFourier--;
        Values = fourier[currentFourier].GetValues();
    }
    else {
        currentFourier = -1;
        Values = { 0,0,0 };
        TotalFouriersHad = 0;
    }
        
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
    for (int i = 0; i < (int)fourier.size(); i++) {
        if (fourier[i].IsOccupied())
            return true;
    }
    return false;
}

void Engine::SetFourier(int N)
{
    currentFourier = N;
    Values = fourier[currentFourier].GetValues();
    PressingButton = false;
}

void Engine::LoadFromFile(std::string filename)
{
    std::string location = "SaveFiles/" + filename + ".dat";
    FILE* file = fopen(location.c_str(), "r");
    if (!file)
        return;
    fourier.clear();
    settings.EmptySelector();
    int N = 0;
    char* name = (char*)calloc(10,sizeof(char));
    fscanf(file, "Number of functions: %i\n", &N);
    TotalFouriersHad = 0;
    if (!N) {
        currentFourier = -1;
        return;
    }
        
    for (int i = 0; i < N; i++) {
        fscanf(file, "%s\nFourier Depth: %i\nSmoothness: %i\nPoints: %i\n",name,&Values[2],&Values[1],&Values[0]);
        float* x = (float*)calloc(Values[0], sizeof(float));
        float* y = (float*)calloc(Values[0], sizeof(float));
        for (int j = 0; j < Values[0]; j++)
            fscanf(file, "%f %f\n", &x[j], &y[j]);
        fourier.push_back(Fourier(Values, x, y));
        TotalFouriersHad++;
        settings.AddToSelector((std::string)name);
    }
    fclose(file);
    SetFourier(0);
    settings.setSelector(0);
    return;
}

void Engine::SaveToFile(std::string filename)
{
    std::string location = "SaveFiles/" + filename + ".dat";
    FILE* file = fopen(location.c_str(), "w");
    fprintf(file, "Number of functions: %i\n", fourier.size());
    for (int i = 0; i < (int)fourier.size(); i++) {
        std::vector<int> iValues = fourier[i].GetValues();
        std::string FunctionName = settings.getSelectorString(i);
        FunctionName.erase(remove(FunctionName.begin(), FunctionName.end(), ' '), FunctionName.end());
        fprintf(file, "%s\nFourier Depth: %i\nSmoothness: %i\nPoints: %i\n", FunctionName.c_str(), iValues[2], iValues[1], iValues[0]);
        for (int j = 0; j < iValues[0]; j++)
            fprintf(file, "%.4f %.4f\n", fourier[i].getPosition(j).x, fourier[i].getPosition(j).y);
    }
    fclose(file);
}

void Engine::ButtonsActions(int ButtonPressed)
{
    if (ButtonPressed)
        change();
    if (ButtonPressed == Settings::IncreaseDepth && currentFourier != -1)
        Values[FourierDepth]++;
    else if (ButtonPressed == Settings::DecreaseDepth && Values[FourierDepth] > 2 && currentFourier != -1)
        Values[FourierDepth]--;
    else if (ButtonPressed == Settings::IncreaseSmoothness && currentFourier != -1)
        Values[PointsFunction] += 10;
    else if (ButtonPressed == Settings::DecreaseSmoothness && Values[PointsFunction] > 10 && currentFourier != -1)
        Values[PointsFunction] -= 10;
    else if (ButtonPressed == Settings::IncreasePoints && currentFourier != -1)
        fourier[currentFourier].AddPointstoDataSet(++Values[FourierPoints]);
    else if (ButtonPressed == Settings::DecreasePoints && currentFourier != -1 && Values[FourierPoints] > 3)
        fourier[currentFourier].AddPointstoDataSet(--Values[FourierPoints]);
    else if (ButtonPressed == Settings::Reset)
        Reset();
    else if (ButtonPressed == Settings::Draw && currentFourier != -1)
        fourier[currentFourier].Draw();
    else if (ButtonPressed == Settings::New)
        AddFourier();
    else if (ButtonPressed == Settings::Delete)
        DeleteFourier();
    else if (ButtonPressed == Settings::Load)
        LoadFromFile(Popup::InputString());
    else if (ButtonPressed == Settings::Save)
        SaveToFile(Popup::InputString());
    else if (ButtonPressed >= 15)
        SetFourier(ButtonPressed - 15);
}
