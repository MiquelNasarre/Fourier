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

void Engine::EventCheck(RenderWindow& window)
{
    SomethingHasChanged = false;
    Event event;
    WindowMovement(window.getPosition());
    Vector2f MousePosition = Renderer::R2Pos((Vector2f)Mouse::getPosition(), WindowPosition, Rend->getScale());
    
    // Everrything to do with settings events
    if (currentFourier!=-1 && fourier[currentFourier].IsDrawing())
        Values[FourierPoints] = fourier[currentFourier].GetNumberPoints();
    settings.setValues(Values);
    ButtonsActions(settings.EventCheck(MouseWindowPosition(), fouriersOccupied(), PressingButton));
    if (currentFourier != -1)
        fourier[currentFourier].setName(settings.selector.getString(currentFourier));
    
    // Everything to do with function events
    if (!PressingButton && currentFourier != -1)
        fourier[currentFourier].EventCheck(SomethingHasChanged, MousePosition, Rend->getScale(), Values);

    //  Blender Events
    if (blender.EventCheck(MouseWindowPosition(), fourier))
        change();
    if (currentFourier != -1) {
        settings.setPointsVisibility(fourier[currentFourier].GetPointsVisibility());
        settings.setFunctionVisibility(fourier[currentFourier].GetFunctionVisibility());
    }
    
    


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
    std::string String = "Untitled " + std::to_string(TotalFouriersHad);
    settings.selector.pushBack(String);
    fourier.push_back(Fourier(ColorWheel(TotalFouriersHad),String));
    currentFourier = fourier.size() - 1;
    fourier[currentFourier].CreateDataSet(DefaultInitialPoints, InitialRadius);
    Values.clear();
    Values.push_back(DefaultInitialPoints);
    Values.push_back(DefaultPointsFunction);
    Values.push_back(DefaultFourierDepth);
    PressingButton = false;
    settings.setPointsVisibility(true);
    settings.setFunctionVisibility(true);
}

void Engine::DeleteFourier()
{
    if (currentFourier == -1)
        return;
    settings.selector.erase();
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

void Engine::DuplicateFourier()
{
    std::string String = settings.selector.getString(currentFourier);
    if (String[String.size() - 1] == ')') {
        std::vector<int> N;
        String.pop_back();
        while (String[String.size() - 1] != '(') {
            N.push_back((int)String[String.size() - 1] - 48);
            if (String.size() == 1 || (int)String[String.size() - 1] - 48 < 0 || (int)String[String.size() - 1] - 48 > 9) {
                N.clear();
                String = settings.selector.getString(currentFourier) + "(1)";
                break;
            }
            else
                String.pop_back();
        }
        int n = 0;
        for (int i = 0; i < (int)N.size(); i++)
            n += N[i] * (int)pow(10, i);
        if(n)
            String = String + std::to_string(n + 1) + ')';
    }
    else
        String = String + "(1)";
    settings.selector.pushBack(String);
    fourier.push_back(fourier[currentFourier]);
    currentFourier = fourier.size() - 1;
    fourier[currentFourier].ResetRandomPointer();
    
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
    settings.selector.clear();
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
        fourier.push_back(Fourier(Values, x, y, Name, color));
        fourier[i].SetPointsVisibility(v0);
        fourier[i].SetFunctionVisibility(v1);
        TotalFouriersHad++;
        settings.selector.pushBack(Name);
    }
    blender.LoadFile(file, fourier);
    fclose(file);
    SetFourier(currentFourier);
    settings.selector.setCurrentSelected(currentFourier);
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
        std::string FunctionName = settings.selector.getString(i);
        Color color = fourier[i].GetFunctionColor();
        fprintf(file, "%s\n%hhi %hhi\nFourier Depth: %i\nSmoothness: %i\nPoints: %i\nColor: %hhi %hhi %hhi %hhi\n", FunctionName.c_str(),fourier[i].GetPointsVisibility(), fourier[i].GetFunctionVisibility(), iValues[2], iValues[1], iValues[0], color.r, color.g, color.b, color.a);
        for (int j = 0; j < iValues[0]; j++)
            fprintf(file, "%.4f %.4f\n", fourier[i].getPosition(j).x, fourier[i].getPosition(j).y);
    }
    blender.SaveFive(file, fourier);
    fclose(file);
}

void Engine::ButtonsActions(int ButtonPressed)
{
    if (!ButtonPressed)
        return;
    change();
    switch (ButtonPressed)
    {
    case(Settings::IncreaseDepth):
        if (currentFourier != -1)
            Values[FourierDepth]++;
        return;
    case(Settings::DecreaseDepth):
        if (currentFourier != -1)
            Values[FourierDepth]--;
        return;
    case(Settings::IncreaseSmoothness):
        if (currentFourier != -1)
            Values[PointsFunction] += 10;
        return;
    case(Settings::DecreaseSmoothness):
        if (currentFourier != -1)
            Values[PointsFunction] -= 10;
        return;
    case(Settings::IncreasePoints):
        if (currentFourier != -1)
            fourier[currentFourier].AddPointstoDataSet(++Values[FourierPoints]);
        return;
    case(Settings::DecreasePoints):
        if (currentFourier != -1)
            fourier[currentFourier].AddPointstoDataSet(--Values[FourierPoints]);
        return;
    case(Settings::Reset):
        if (currentFourier != -1)
            DuplicateFourier();
        return;
    case(Settings::Draw):
        if (currentFourier != -1) {
            fourier[currentFourier].Draw();
            settings.setPointsVisibility(true);
            settings.close();
            blender.Close();
        }
        return;
    case(Settings::Delete):
        if (currentFourier != -1)
            DeleteFourier();
        return;
    case(Settings::Save):
        if (currentFourier != -1)
            SaveToFile(Popup::InputString("Choosa a file name", 50));
        return;
    case(Settings::ColorSelector):
        if (currentFourier != -1)
            fourier[currentFourier].SetFunctionColor(Popup::ColorSelection(fourier[currentFourier].GetFunctionColor()));
        return;
    case(Settings::HidePoints):
        if (currentFourier != -1)
            fourier[currentFourier].SetPointsVisibility(false);
        return;
    case(Settings::ShowPoints):
        if (currentFourier != -1)
            fourier[currentFourier].SetPointsVisibility(true);
        return;
    case(Settings::HideFunction):
        if (currentFourier != -1)
            fourier[currentFourier].SetFunctionVisibility(false);
        return;
    case(Settings::ShowFunction):
        if (currentFourier != -1)
            fourier[currentFourier].SetFunctionVisibility(true);
        return;
    case(Settings::New):
        AddFourier();
        return;
    case(Settings::Load):
        LoadFromFile(Popup::InputString("Name of the file", 50));
        return;
    case(Settings::HideGrid):
        ShowGrid = false;
        return;
    case(Settings::ShowGrid):
        ShowGrid = true;
        return;
    }
    if (ButtonPressed >= 30)
        SetFourier(ButtonPressed - 30);
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
    srand((unsigned int)time(nullptr));
}

void Engine::MainLoop()
{
    RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "Fourier Plotter", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(InitialWinPos);
    Renderer renderer(window);
    Rend = &renderer;
    window.setFramerateLimit(60);

    //  Icona guai posada :3
    Image icon;
    icon.loadFromFile("Resources/Textures/Icon.png");
    TransparentGreenScreen(&icon);
    window.setIcon(51,51, icon.getPixelsPtr());

    settings.open();

    while (window.isOpen())
    {
        EventCheck(window);
        if (window.hasFocus() && SomethingHasChanged) {
            window.clear(Color::White);
            if(ShowGrid)
                renderer.renderPlain(window.getPosition());
            for (int i = 0; i < (int)fourier.size(); i++) {
                if(fourier[i].GetFunctionVisibility())
                    fourier[i].RenderFunction(renderer);
            }
            if (currentFourier != -1 && fourier[currentFourier].GetPointsVisibility())
                fourier[currentFourier].RenderPoints(renderer);
            settings.Render(renderer);
            blender.Render(renderer);
            window.display();
        }

        else {
using namespace std;
            this_thread::sleep_for(30ms);
using namespace sf;
        }
    }
}


