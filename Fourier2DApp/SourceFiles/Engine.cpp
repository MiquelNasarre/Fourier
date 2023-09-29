#include "Engine.h"

Color Engine::ColorWheel(int n)
{
    switch (n%7)
    {
    case 0:
        return Color::Red;
    case 1:
        return Color::Green;
    case 2:
        return Color::Blue;
    case 3:
        return Color::Yellow;
    case 4:
        return Color::Magenta;
    case 5:
        return Color::Cyan;
    case 6:
        return Color::Black;
    }
    return Color();
}

//  Public

Engine::Engine()
{   
    Values.push_back(DefaultInitialPoints);
    Values.push_back(DefaultPointsFunction);
    Values.push_back(DefaultFourierDepth);
    fourier.push_back(Fourier(ColorWheel(TotalFouriersHad)));
    fourier[0].CreateDataSet(Values[FourierPoints]);
    TotalFouriersHad++;
}

void Engine::MainLoop()
{
    RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "Fourier Plotter", Style::Default);
    window.setPosition(InitialWinPos);
    Renderer renderer(window);
    Rend = &renderer;
    window.setFramerateLimit(60);

    //  Posali una icona mes guai
    Uint8 P[2] = { (Uint8)0xffffff,(Uint8)0xffffff };
    window.setIcon(1, 2, P);

    while (window.isOpen())
    {
        EventCheck(window);
        if (window.hasFocus() && SomethingHasChanged) {
            renderer.renderPlain(window.getPosition());
            for (int i = 0; i < (int)fourier.size(); i++) {
                if(fourier[i].GetFunctionVisibility())
                    fourier[i].RenderFunction(renderer);
            }
            if (currentFourier != -1 && fourier[currentFourier].GetPointsVisibility())
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
    fourier.push_back(Fourier(ColorWheel(TotalFouriersHad)));
    TotalFouriersHad++;
    currentFourier = fourier.size() - 1;
    fourier[currentFourier].CreateDataSet(DefaultInitialPoints, InitialRadius);
    Values.clear();
    Values.push_back(DefaultInitialPoints);
    Values.push_back(DefaultPointsFunction);
    Values.push_back(DefaultFourierDepth);
    PressingButton = false;
    settings.setPointsVisibility(true);
    settings.setFunctionVisibility(true);
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
        settings.setPointsVisibility(fourier[currentFourier].GetPointsVisibility());
        settings.setFunctionVisibility(fourier[currentFourier].GetFunctionVisibility());
    }
    else {
        currentFourier = -1;
        Values = { 0,0,0 };
        TotalFouriersHad = 0;
        settings.setPointsVisibility(false);
        settings.setFunctionVisibility(false);
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
    settings.setPointsVisibility(fourier[currentFourier].GetPointsVisibility());
    settings.setFunctionVisibility(fourier[currentFourier].GetFunctionVisibility());
}

void Engine::LoadFromFile(std::string filename)
{
    if (!filename.size())
        return;
    std::string location = "SaveFiles/" + filename + ".dat";
    FILE* file = fopen(location.c_str(), "r");
    if (!file)
        return;
    fourier.clear();
    settings.EmptySelector();
    int N = 0;
    std::string Name;
    fscanf(file, "Number of functions: %i %i\n", &N, &currentFourier);
    TotalFouriersHad = 0;
    if (!N) {
        currentFourier = -1;
        return;
    }
        
    for (int i = 0; i < N; i++) {
        char c = 'P';
        Name.clear();
        fscanf(file, "%c", &c);
        while (c != L'\n') {
            Name.push_back(c);
            fscanf(file, "%c", &c);
        }
        Color color;
        int v0, v1;
        fscanf(file, "%i %i\nFourier Depth: %i\nSmoothness: %i\nPoints: %i\nColor: %hhi %hhi %hhi %hhi\n",&v0,&v1,&Values[2],&Values[1],&Values[0],&color.r,&color.g,&color.b,&color.a);
        float* x = (float*)calloc(Values[0], sizeof(float));
        float* y = (float*)calloc(Values[0], sizeof(float));
        for (int j = 0; j < Values[0]; j++)
            fscanf(file, "%f %f\n", &x[j], &y[j]);
        fourier.push_back(Fourier(Values, x, y, color));
        fourier[i].SetPointsVisibility(v0);
        fourier[i].SetFunctionVisibility(v1);
        TotalFouriersHad++;
        settings.AddToSelector(Name);
    }
    fclose(file);
    SetFourier(currentFourier);
    settings.setSelector(currentFourier);
    return;
}

void Engine::SaveToFile(std::string filename)
{
    if (!filename.size())
        return;
    std::string location = "SaveFiles/" + filename + ".dat";
    FILE* file = fopen(location.c_str(), "w");
    fprintf(file, "Number of functions: %i %i\n", fourier.size(), currentFourier);
    for (int i = 0; i < (int)fourier.size(); i++) {
        std::vector<int> iValues = fourier[i].GetValues();
        std::string FunctionName = settings.getSelectorString(i);
        Color color = fourier[i].GetFunctionColor();
        fprintf(file, "%s\n%hhi %hhi\nFourier Depth: %i\nSmoothness: %i\nPoints: %i\nColor: %hhi %hhi %hhi %hhi\n", FunctionName.c_str(),fourier[i].GetPointsVisibility(), fourier[i].GetFunctionVisibility(), iValues[2], iValues[1], iValues[0], color.r, color.g, color.b, color.a);
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
    else if (ButtonPressed == Settings::Draw && currentFourier != -1) {
        fourier[currentFourier].Draw();
        settings.setPointsVisibility(true);
    }
    else if (ButtonPressed == Settings::New)
        AddFourier();
    else if (ButtonPressed == Settings::Delete)
        DeleteFourier();
    else if (ButtonPressed == Settings::Load)
        LoadFromFile(Popup::InputString("Name of the file", 50));
    else if (ButtonPressed == Settings::Save)
        SaveToFile(Popup::InputString("Choosa a file name", 50));
    else if (ButtonPressed == Settings::ColorSelector)
        fourier[currentFourier].SetFunctionColor(Popup::ColorSelection(fourier[currentFourier].GetFunctionColor()));
    else if (ButtonPressed == Settings::HidePoints)
        fourier[currentFourier].SetPointsVisibility(false);
    else if (ButtonPressed == Settings::ShowPoints)
        fourier[currentFourier].SetPointsVisibility(true);
    else if (ButtonPressed == Settings::HideFunction)
        fourier[currentFourier].SetFunctionVisibility(false);
    else if (ButtonPressed == Settings::ShowFunction)
        fourier[currentFourier].SetFunctionVisibility(true);
    else if (ButtonPressed >= 30)
        SetFourier(ButtonPressed - 30);
}
