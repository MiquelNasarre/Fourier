#include "Popup.h"

Image Popup::createColorPalete(Vector2i size)
{
    Image image;
    image.create(size.x, size.y);
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            image.setPixel(i, j, PixelColor(i, j, size.x, size.y));
        }
    }
    return image;
}

Color Popup::PixelColor(int x, int y, int width, int height)
{
    float R;
    float G;
    float B;

    float regionWidth = (float)width / 6.f;
    
    if ((float)x < regionWidth) {
        float RegionX = (float)x / regionWidth;
        R = 255;
        G = 255 * RegionX;
        B = 0;
    }
    else if ((float)x < 2 * regionWidth) {
        float RegionX = ((float)x - regionWidth) / regionWidth;
        R = 255 * (1 - RegionX);
        G = 255;
        B = 0;
    }
    else if ((float)x < 3 * regionWidth) {
        float RegionX = ((float)x - 2 * regionWidth) / regionWidth;
        R = 0;
        G = 255;
        B = (unsigned char)(255 * RegionX);
    }
    else if ((float)x < 4 * regionWidth) {
        float RegionX = ((float)x - 3 * regionWidth) / regionWidth;
        R = 0;
        G = 255 * (1 - RegionX);
        B = 255;
    }
    else if ((float)x < 5 * regionWidth) {
        float RegionX = ((float)x - 4 * regionWidth) / regionWidth;
        R = 255 * RegionX;
        G = 0;
        B = 255;
    }
    else {
        float RegionX = ((float)x - 5 * regionWidth) / regionWidth;
        R = 255;
        G = 0;
        B = 255 * (1 - RegionX);
    }
    float PercentageY = (float)y / (float)height;

    R = R - (R - 127) * PercentageY;
    G = G - (G - 127) * PercentageY;
    B = B - (B - 127) * PercentageY;
    


    return Color((unsigned char)R, (unsigned char)G, (unsigned char)B, 255);
}

Vector2i Popup::MousePosition(Window& window)
{
    return Vector2i(Mouse::getPosition().x - window.getPosition().x + Ex, Mouse::getPosition().y - window.getPosition().y - Ey);
}

void Popup::BrightnessSliderImage(Image& image, Vector2i currentSelected)
{
    Color CurrentColor = PixelColor(currentSelected.x, currentSelected.y, 256, 256);
    float R = (float)CurrentColor.r;
    float G = (float)CurrentColor.g;
    float B = (float)CurrentColor.b;
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 20; j++)
            image.setPixel(i, j, Color((unsigned char)(R * i / 128), (unsigned char)(G * i / 128), (unsigned char)(B * i / 128), 255));
    }
    for (int i = 128; i < 256; i++) {
        for (int j = 0; j < 20; j++)
            image.setPixel(i, j, Color((unsigned char)(R + (255 - R) * (i - 127) / 128), (unsigned char)(G + (255 - G) * (i - 127) / 128), (unsigned char)(B + (255 - B) * (i - 127) / 128), 255));
    }
}

Vector3i Popup::InversePixelColor(Color current, int width, int height)
{
    float L, M, S;
    if (current.r > current.g) {
        if (current.r > current.b) {
            L = current.r;
            if (current.b > current.g) {
                M = current.b;
                S = current.g;
            }
            else {
                M = current.g;
                S = current.b;
            }
        }
        else {
            L = current.b;
            M = current.r;
            S = current.g;
        }
    }
    else {
        if (current.g > current.b) {
            L = current.g;
            if (current.b > current.r) {
                M = current.b;
                S = current.r;
            }
            else {
                M = current.r;
                S = current.b;
            }
        }
        else {
            L = current.b;
            M = current.g;
            S = current.r;
        }
    }
    float x, y, z;
    if (128 * S / 32385 + L / 255 > 1) {
        if (L == S && S == 255)
            x = 1;
        else
            x = 255 * (L - 255) / (128 * S + 127 * L - 65025);
        y = 127 * L / 32640 + S / 255 + 1 / 128;
    }
    else {
        if (L == S && S == 0)
            x = 1;
        else
            x = 255 * S / (128 * S + 127 * L);
        y = 128 * S / 32385 + L / 255;
    }
    if (L == S)
        z = 0;
    else
        z = 255 * (S - M) / (S - L);
    
    if (L == current.r && M == current.g)
        z = z / 6;
    else if (L == current.g && M == current.r)
        z = 255 / 6 * 2 - z / 6;
    else if (L == current.g && M == current.b)
        z = 255 / 6 * 2 + z / 6;
    else if (L == current.b && M == current.g)
        z = 255 / 6 * 4 - z / 6;
    else if (L == current.b && M == current.r)
        z = 255 / 6 * 4 + z / 6;
    else if (L == current.r && M == current.b)
        z = 255 - z / 6;
    return Vector3i((int)z, (int)(x * 255), (int)(y * 255 / 2));
}

//  Public

std::string Popup::InputString(std::string WindowName, int MaxSize) {
    Text text;
    Font font;
    font.loadFromFile(ArialFontFile);
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(15);
    Button Cancel("Resources/Textures/CustomButtons.png", std::vector<Vector2i>({ Vector2i(0, 3),Vector2i(0,36),Vector2i(0,69) }), Vector2i(89, 32), Vector2f(1.5f, 1.f), Vector2f(8.f, 50.f), true,"Cancel",Vector2f(40.f,6.f),font,16);
    Button Enter("Resources/Textures/CustomButtons.png", std::vector<Vector2i>({ Vector2i(0, 3),Vector2i(0,36),Vector2i(0,69) }), Vector2i(89, 32), Vector2f(1.5f, 1.f), Vector2f(160.f, 50.f), true, "Enter", Vector2f(47.f, 6.f), font, 16);
    Texture TexBack;
    TexBack.loadFromFile("Resources/Textures/CustomButtons.png", IntRect(0, 36, 89, 32));
    Sprite BackText(TexBack);
    BackText.setPosition(18.f, 4.f);
    BackText.setScale(3.f, 1.f);
    BackText.setColor(Color(255, 255, 255, 100));
    RenderWindow window(VideoMode(300, 90), WindowName, Style::Titlebar);
    window.setFramerateLimit(60);
    Renderer renderer(window);

    Image icon;
    icon.loadFromFile("Resources/Textures/TextPopupIcon.png");
    TransparentGreenScreen(&icon);
    window.setIcon(26, 26, icon.getPixelsPtr());

    std::string name;

    while (window.isOpen()) {
        window.setActive();
        window.requestFocus();
        if (Cancel.eventCheck(Vector2i(Mouse::getPosition().x - window.getPosition().x + Ex, Mouse::getPosition().y - window.getPosition().y - Ey)) == Button::Pressed)
            return "";
        if (Enter.eventCheck(Vector2i(Mouse::getPosition().x - window.getPosition().x + Ex, Mouse::getPosition().y - window.getPosition().y - Ey)) == Button::Pressed && name.size())
            return name;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
            else if (event.type == Event::TextEntered) {
                if (event.text.unicode == 13 && name.size()) {
                    return name;
                }
                else if (event.text.unicode == 8 && name.size())
                    name.pop_back();
                else if ((int)name.size() < MaxSize && event.text.unicode != 8 && event.text.unicode != 13)
                    name.push_back(event.text.unicode);
            }
        }

        window.clear(Color::White);
        text.setString(name);
        text.setPosition(150.f - text.getLocalBounds().getSize().x / 2, 10.f);
        window.draw(BackText);
        window.draw(text);
        Cancel.Render(window);
        Enter.Render(window);
        window.display();
    }

    return "";
}

Color Popup::ColorSelection(Color Current)
{

    Image image = createColorPalete();
    Texture texture;
    texture.loadFromImage(image);
    Sprite sprite(texture);
    sprite.setPosition(22.f, 22.f);
    Texture PointerTexture;
    image.loadFromFile("Resources/Textures/CustomButtons.png");
    TransparentGreenScreen(&image);
    PointerTexture.loadFromImage(image, IntRect(377,6, 15, 15));
    Sprite Pointer(PointerTexture);
    Pointer.setPosition(-10.f, -10.f);
    
    std::string String = "R:\n\n\nG:\n\n\nB:\n\n\nA:";
    Font font;
    font.loadFromFile(ArialFontFile);
    Text AllText;
    AllText.setFont(font);
    AllText.setCharacterSize(14);
    AllText.setFillColor(Color::Black);
    AllText.setString(String);
    AllText.setPosition(297.f, 100.f);

    Texture SliderPointerTexture;
    SliderPointerTexture.loadFromImage(image, IntRect(402, 9, 7, 38));
    Sprite SliderPointer(SliderPointerTexture);

    Texture BrightnessTexture;
    image.create(256, 20);
    BrightnessTexture.loadFromImage(image);
    Sprite BrightnessSlider(BrightnessTexture);
    BrightnessSlider.setPosition(22.f, 300.f);

    
    Button EnterButton("Resources/Textures/CustomButtons.png", std::vector<Vector2i>({ Vector2i(363,460),Vector2i(413,460),Vector2i(463,460) }), Vector2i(48, 53), Vector2f(1.3f, 1.f), Vector2f(293.f, 283.f),true, "Select",Vector2f(8.f,16.f),font,16);

    std::vector<RectangleShape> Background;
    Background.push_back(RectangleShape(Vector2f(260.f, 260.f)));
    Background[0].setFillColor(Color(170, 170, 170, 255));
    Background[0].setPosition(20.f, 20.f);
    Background.push_back(RectangleShape(Vector2f(260.f, 24.f)));
    Background[1].setFillColor(Color(170, 170, 170, 255));
    Background[1].setPosition(20.f, 298.f);
    Background.push_back(RectangleShape(Vector2f(54.f, 54.f)));
    Background[2].setFillColor(Color(170, 170, 170, 255));
    Background[2].setPosition(298.f, 20.f);

    
    Color currentColor = Current;
    Vector3i temp = InversePixelColor(currentColor, 256, 256);
    Vector2i currentSelected(temp.x,temp.y);
    int currentBrightness(temp.z);
    Pointer.setPosition((float)temp.x - 8.f + 23.f, (float)temp.y - 8.f + 23.f);
    SliderPointer.setPosition((float)temp.z - 2.f + 23.f, 292.f);
    BrightnessSliderImage(image, currentSelected);
    BrightnessTexture.loadFromImage(image);

    RectangleShape CurrentDisplay(Vector2f(50.f, 50.f));
    CurrentDisplay.setPosition(300.f, 22.f);
    CurrentDisplay.setFillColor(currentColor);

    NumberBar R(DefaultNumberBarInitializer, Vector2f(315.f, 98.f), 255, 0, currentColor.r, font);
    NumberBar G(DefaultNumberBarInitializer, Vector2f(315.f, 146.f), 255, 0, currentColor.g, font);
    NumberBar B(DefaultNumberBarInitializer, Vector2f(315.f, 194.f), 255, 0, currentColor.b, font);
    NumberBar A(DefaultNumberBarInitializer, Vector2f(315.f, 242.f), 255, 0, currentColor.a, font);

    Vector2i MousePos;
    RenderWindow window(VideoMode(370, 350), "Color Selector", sf::Style::Titlebar | sf::Style::Close);

    Image icon;
    icon.loadFromFile("Resources/Textures/ColorPopupIcon.png");
    TransparentGreenScreen(&icon);
    window.setIcon(20, 20, icon.getPixelsPtr());
    
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        MousePos = MousePosition(window);
        window.requestFocus();
        if (EnterButton.eventCheck(MousePos) == 3)
            return currentColor;
        Event event;
        while (window.pollEvent(event)) {
            
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) || event.type == Event::Closed) {
                window.close();
                return Current;
            }
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)) {
                window.close();
                return currentColor;
            }
            if (R.EventCheck(event, MousePos) == 2 || G.EventCheck(event, MousePos) == 2 || B.EventCheck(event, MousePos) == 2 || A.EventCheck(event, MousePos) == 2) {
                currentColor = Color(R.getNumber(),G.getNumber(),B.getNumber(),A.getNumber());
                temp = InversePixelColor(currentColor, 256, 256);
                currentSelected = Vector2i(temp.x, temp.y);
                currentBrightness = temp.z;
                Pointer.setPosition((float)temp.x - 8.f + 23.f, (float)temp.y - 8.f + 23.f);
                SliderPointer.setPosition((float)temp.z - 2.f + 23.f, 292.f);
                BrightnessSliderImage(image, currentSelected);
                BrightnessTexture.loadFromImage(image);
                CurrentDisplay.setFillColor(currentColor);
            }
        }
        if (Mouse::isButtonPressed(Mouse::Left) && MousePos.x > 22 && MousePos.x <= 278 && MousePos.y > 22 && MousePos.y <= 278) {
            Pointer.setPosition((float)MousePos.x - 8.f, (float)MousePos.y - 8.f);
            currentSelected = Vector2i(MousePos.x - 23, MousePos.y - 23);
            currentBrightness = 127;
            BrightnessSliderImage(image, currentSelected);
            BrightnessTexture.loadFromImage(image);
            SliderPointer.setPosition((float)currentBrightness + 23.f - 2.f, 292.f);
            currentColor = image.getPixel(currentBrightness, 0);
            CurrentDisplay.setFillColor(currentColor);
            R.setNumber(currentColor.r);
            G.setNumber(currentColor.g);
            B.setNumber(currentColor.b);
            A.setNumber(currentColor.a);
        }

        else if (Mouse::isButtonPressed(Mouse::Left) && MousePos.x > 22 && MousePos.x <= 278 && MousePos.y > 300 && MousePos.y <= 320) {
            SliderPointer.setPosition((float)MousePos.x - 2.f, 292.f);
            currentBrightness = MousePos.x - 23;
            currentColor = image.getPixel(currentBrightness, 0);
            CurrentDisplay.setFillColor(currentColor);
            R.setNumber(currentColor.r);
            G.setNumber(currentColor.g);
            B.setNumber(currentColor.b);
            A.setNumber(currentColor.a);
        }
            
        window.clear(Color::White);
        window.draw(Background[0]);
        window.draw(Background[1]);
        window.draw(Background[2]);
        window.draw(CurrentDisplay);
        window.draw(sprite);
        window.draw(Pointer);
        window.draw(BrightnessSlider);
        window.draw(SliderPointer);
        R.Render(window);
        G.Render(window);
        B.Render(window);
        A.Render(window);
        EnterButton.Render(window);
        window.draw(AllText);
        window.display();
    }
    return currentColor;
}
