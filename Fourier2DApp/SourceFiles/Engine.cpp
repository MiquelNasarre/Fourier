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
    Change = false;
    Vector2f MouseR2 = Renderer::R2Pos(Mouse::getPosition(), WindowPosition, renderer.getScale());
    Vector2i MousePos = mousePosition();

    //  Other
    Event event;
    WindowMovement(window.getPosition());
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseWheelMoved) {
            renderer.ModifyScale((float)event.mouseWheel.delta);
            change();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.control) {
            if (event.key.code == sf::Keyboard::Z)
                loadPrev();
            if (event.key.code == sf::Keyboard::Y)
                loadNext();
        }
    }
    
    //  ToolBox Events
    bool Save = false;
    std::vector<Point> toolPoints;
    if (currentFourier != -1)
        toolPoints = *fourier[currentFourier].GetPoints();
    if (currentFourier == -1) {
        if (toolBox.Close())
            change();
    }
    else if (toolBox.EventCheck(MousePos, fourier[currentFourier], Save, currentFourier)) {
        if (Save)
            pushState(SaveState::Modify, currentFourier, toolPoints, fourier[currentFourier].GetFunctionColor(), Values, fourier[currentFourier].getName());
        change();
    }

    // Everrything to do with settings events
    if (currentFourier != -1) {
        settings.setPointsVisibility(fourier[currentFourier].GetPointsVisibility());
        settings.setFunctionVisibility(fourier[currentFourier].GetFunctionVisibility());
        if (fourier[currentFourier].getName() != settings.selector.getString(currentFourier)) {
            pushState(SaveState::Modify);
            fourier[currentFourier].setName(settings.selector.getString(currentFourier));
        }
        fourier[currentFourier].setName(settings.selector.getString(currentFourier));
        Values = fourier[currentFourier].GetValues();
    }
    settings.setValues(Values);
    ButtonsActions(settings.EventCheck(MousePos, fouriersOccupied(), PressingButton));
    
    //  Blender Events
    if (blender.EventCheck(MousePos, fourier))
        change();

    // Everything to do with function events
    Save = false;
    if (currentFourier != -1)
        fourier[currentFourier].EventCheck(Change, MouseR2, renderer.getScale(), Values, Save);
    if (Save)
        pushState(SaveState::Modify, currentFourier, toolPoints, fourier[currentFourier].GetFunctionColor(), Values, fourier[currentFourier].getName());
}

void Engine::AddFourier()
{
    TotalFouriersHad++;
    pushState(SaveState::Create, fourier.size());
    std::string String = "Untitled " + std::to_string(TotalFouriersHad);
    settings.selector.pushBack(String);
    fourier.push_back(Fourier(ColorWheel(TotalFouriersHad - 1),String));
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
    pushState(SaveState::Delete, currentFourier, *fourier[currentFourier].GetPoints(), fourier[currentFourier].GetFunctionColor(), fourier[currentFourier].GetValues(),fourier[currentFourier].getName());
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
    pushState(SaveState::Create, fourier.size());
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

Vector2i Engine::mousePosition()
{
    return Vector2i(Mouse::getPosition().x - WindowPosition.x + Ex, Mouse::getPosition().y - WindowPosition.y - Ey);
}

void Engine::WindowMovement(Vector2i NewWindowPosition)
{
    if (WindowPosition != NewWindowPosition) {
        WindowPosition = NewWindowPosition;
        renderer.SetWindowPos(WindowPosition);
        change();
    }
}

void Engine::change()
{
    Change = true;
}

bool Engine::fouriersOccupied()
{
    for (int i = 0; i < (int)fourier.size(); i++) {
        if (fourier[i].IsOccupied())
            return true;
    }
    return false;
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
    saveStates.clear();
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

void Engine::purgeStates()
{
    while (currentState < (int)saveStates.size() - 1)
        saveStates.pop_back();
}

void Engine::pushState(int Nature)
{
    purgeStates();
    saveStates.push_back(SaveState(Nature, currentFourier, *fourier[currentFourier].GetPoints(), fourier[currentFourier].GetFunctionColor(), fourier[currentFourier].GetValues(), fourier[currentFourier].getName()));
    currentState++;
    if (Nature == SaveState::Delete)
        blender.getBlenders(saveStates[currentState], fourier);
}

void Engine::pushState(int nature, int identifier)
{
    purgeStates();
    saveStates.push_back(SaveState(nature, identifier));
    currentState++;
    if (nature == SaveState::Delete)
        blender.getBlenders(saveStates[currentState], fourier);
}

void Engine::pushState(int nature, int identifier, std::vector<Point> points, Color color, std::vector<int> values, std::string name)
{
    purgeStates();
    saveStates.push_back(SaveState(nature, identifier, points, color, values, name));
    currentState++;
    if (nature == SaveState::Delete)
        blender.getBlenders(saveStates[currentState], fourier);
}

void Engine::loadPrev()
{
    if (currentState == -1)
        return;
    change();
    SaveState state = saveStates[currentState];
    
    if (state.Location == SaveState::FourierLocated) {
        if (state.Nature == SaveState::Modify) {
            currentFourier = state.Identifier;
            saveStates[currentState] = SaveState(SaveState::Modify, currentFourier, *fourier[currentFourier].GetPoints(), fourier[currentFourier].GetFunctionColor(), fourier[currentFourier].GetValues(), fourier[currentFourier].getName());
            Values = state.Values;
            fourier[currentFourier].CreateDataSet(state.Fourier.size());
            fourier[currentFourier].SetDepth(Values[FourierDepth]);
            for (int i = 0; i < (int)state.Fourier.size(); i++)
                fourier[currentFourier].SetPointPosition(i, state.Fourier[i]);
            fourier[currentFourier].setName(state.Name);
            fourier[currentFourier].SetFunctionColor(state.FourierColor);
            settings.selector.setName(fourier[currentFourier].getName());
        }
        else if (state.Nature == SaveState::Create) {
            saveStates[currentState] = SaveState(SaveState::Delete, state.Identifier, *fourier[state.Identifier].GetPoints(), fourier[state.Identifier].GetFunctionColor(), fourier[state.Identifier].GetValues(), fourier[state.Identifier].getName());
            fourier.erase(fourier.begin() + state.Identifier);
            settings.selector.erase(state.Identifier);
            if (currentFourier == fourier.size())
                currentFourier--;
            settings.selector.setCurrentSelected(currentFourier);
            if (!fourier.size()) {
                Values = { 0,0,0 };
                TotalFouriersHad = 0;
                settings.setPointsVisibility(false);
                settings.setFunctionVisibility(false);
            }
        }
        else if (state.Nature == SaveState::Delete) {
            currentFourier = state.Identifier;
            saveStates[currentState] = SaveState(SaveState::Create, state.Identifier);
            if (!TotalFouriersHad)
                TotalFouriersHad++;
            fourier.insert(fourier.begin() + state.Identifier, Fourier(state.FourierColor,state.Name));
            
            settings.selector.insert(state.Identifier, state.Name);
            fourier[currentFourier].CreateDataSet(state.Fourier.size());
            Values = state.Values;
            fourier[currentFourier].SetDepth(Values[FourierDepth]);
            for (int i = 0; i < (int)state.Fourier.size(); i++)
                fourier[currentFourier].SetPointPosition(i, state.Fourier[i]);
        }
        if (currentFourier != -1) {
            fourier[currentFourier].GenerateS0();
            fourier[currentFourier].GraphFunctionS0(Values[PointsFunction]);
        }
        blender.getBlenders(saveStates[currentState], fourier);
        blender.setBlenders(state, fourier);
    }
    currentState--;
}

void Engine::loadNext()
{
    if (saveStates.size() - 1 == currentState)
        return;
    change();
    currentState++;
    SaveState state = saveStates[currentState];

    if (state.Location == SaveState::FourierLocated) {
        if (state.Nature == SaveState::Modify) {
            currentFourier = state.Identifier;
            saveStates[currentState] = SaveState(SaveState::Modify, currentFourier, *fourier[currentFourier].GetPoints(), fourier[currentFourier].GetFunctionColor(), fourier[currentFourier].GetValues(), fourier[currentFourier].getName());
            Values = state.Values;
            fourier[currentFourier].CreateDataSet(state.Fourier.size());
            fourier[currentFourier].SetDepth(Values[FourierDepth]);
            for (int i = 0; i < (int)state.Fourier.size(); i++)
                fourier[currentFourier].SetPointPosition(i, state.Fourier[i]);
            fourier[currentFourier].setName(state.Name);
            fourier[currentFourier].SetFunctionColor(state.FourierColor);
            settings.selector.setName(fourier[currentFourier].getName());
        }
        else if (state.Nature == SaveState::Create) {
            saveStates[currentState] = SaveState(SaveState::Delete, state.Identifier, *fourier[state.Identifier].GetPoints(), fourier[state.Identifier].GetFunctionColor(), fourier[state.Identifier].GetValues(), fourier[state.Identifier].getName());
            fourier.erase(fourier.begin() + state.Identifier);
            settings.selector.erase(state.Identifier);
            if (currentFourier == fourier.size())
                currentFourier--;
            settings.selector.setCurrentSelected(currentFourier);
            if (!fourier.size()) {
                Values = { 0,0,0 };
                TotalFouriersHad = 0;
                settings.setPointsVisibility(false);
                settings.setFunctionVisibility(false);
            }
        }
        else if (state.Nature == SaveState::Delete) {
            currentFourier = state.Identifier;
            saveStates[currentState] = SaveState(SaveState::Create, currentFourier);
            if (!TotalFouriersHad)
                TotalFouriersHad++;
            fourier.insert(fourier.begin() + state.Identifier, Fourier(state.FourierColor, state.Name));

            settings.selector.insert(state.Identifier, state.Name);
            fourier[currentFourier].CreateDataSet(state.Fourier.size());
            Values = state.Values;
            fourier[currentFourier].SetDepth(Values[FourierDepth]);
            for (int i = 0; i < (int)state.Fourier.size(); i++)
                fourier[currentFourier].SetPointPosition(i, state.Fourier[i]);
        }
        if (currentFourier != -1) {
            fourier[currentFourier].GenerateS0();
            fourier[currentFourier].GraphFunctionS0(Values[PointsFunction]);
        }
        blender.getBlenders(saveStates[currentState], fourier);
        blender.setBlenders(state, fourier);
    }
}

void Engine::ButtonsActions(int ButtonPressed)
{
    if (!ButtonPressed)
        return;
    change();
    switch (ButtonPressed)
    {
    case(Settings::IncreaseDepth):
        if (currentFourier != -1) {
            pushState(SaveState::Modify);
            Values[FourierDepth]++;
        }
        return;
    case(Settings::DecreaseDepth):
        if (currentFourier != -1 && Values[FourierDepth] > 2) {
            pushState(SaveState::Modify);
            Values[FourierDepth]--;
        }
        return;
    case(Settings::IncreaseSmoothness):
        if (currentFourier != -1) {
            pushState(SaveState::Modify);
            Values[PointsFunction] += 10;
        }
        return;
    case(Settings::DecreaseSmoothness):
        if (currentFourier != -1 && Values[PointsFunction] > 10) {
            pushState(SaveState::Modify);
            Values[PointsFunction] -= 10;
        }
        return;
    case(Settings::IncreasePoints):
        if (currentFourier != -1) {
            pushState(SaveState::Modify);
            fourier[currentFourier].AddPointstoDataSet(++Values[FourierPoints]);
        }
        return;
    case(Settings::DecreasePoints):
        if (currentFourier != -1 && Values[FourierPoints] > 3) {
            pushState(SaveState::Modify);
            fourier[currentFourier].AddPointstoDataSet(--Values[FourierPoints]);
        }
        return;
    case(Settings::Reset):
        if (currentFourier != -1)
            DuplicateFourier();
        return;
    case(Settings::Draw):
        if (currentFourier != -1) {
            pushState(SaveState::Modify);
            fourier[currentFourier].Draw();
            settings.setPointsVisibility(true);
            settings.close();
            blender.Close();
            toolBox.Close();
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
        if (currentFourier != -1) {
            pushState(SaveState::Modify);
            fourier[currentFourier].SetFunctionColor(Popup::ColorSelection(fourier[currentFourier].GetFunctionColor()));
        }
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
        currentFourier = ButtonPressed - 30;
}

void Engine::Display(RenderWindow& window)
{
    window.clear(Color::White);

    if (ShowGrid)
        renderer.renderPlain(window.getPosition());
    for (int i = 0; i < (int)fourier.size(); i++)
        fourier[i].RenderFunction(renderer);
    if (currentFourier != -1)
        fourier[currentFourier].RenderPoints(renderer);
    settings.Render(renderer);
    blender.Render(renderer);
    toolBox.Render(renderer);

    window.display();
}

//  Public

Engine::Engine()
    :renderer{ Renderer(window) }
{   
    Values.push_back(DefaultInitialPoints);
    Values.push_back(DefaultPointsFunction);
    Values.push_back(DefaultFourierDepth);
    fourier.push_back(Fourier(ColorWheel(TotalFouriersHad), "Untitled 1"));
    fourier[0].CreateDataSet(Values[FourierPoints]);
    fourier[0].SetDepth(Values[FourierDepth]);
    TotalFouriersHad++;
    srand((unsigned int)time(nullptr));

    window.create(VideoMode(ScreenWidth, ScreenHeight), "Fourier Plotter", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(InitialWinPos);
    window.setFramerateLimit(60);

    //  Icona guai posada :3
    Image icon;
    icon.loadFromFile("Resources/Textures/Icon.png");
    TransparentGreenScreen(&icon);
    window.setIcon(51, 51, icon.getPixelsPtr());
}

void Engine::MainLoop()
{
    while (window.isOpen())
    {
        if(window.hasFocus())
            EventCheck(window);
        if (window.hasFocus() && Change)
            Display(window);
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
