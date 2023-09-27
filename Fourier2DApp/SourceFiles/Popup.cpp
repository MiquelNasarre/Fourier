#include "Popup.h"
#include <wchar.h>

std::string Popup::InputString() {
    Text text;
    Font font;
    font.loadFromFile("Resources/Fonts/arial.ttf");
    text.setFont(font);
    text.setPosition(100.f, 100.f);
    text.setFillColor(Color::Black);

    RenderWindow window(VideoMode(300, 300), "Set a name", Style::Titlebar);
    window.setFramerateLimit(60);
    std::string name;

    while (window.isOpen()) {
        window.setActive();
        window.requestFocus();
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
                else if (name.size() < MaxNameSize && event.text.unicode != 8)
                    name.push_back(event.text.unicode);
            }
        }

        // Dibuja el nombre en la ventana
        window.clear(Color::White);
        text.setString(name);
        window.draw(text);
        window.display();
    }

    return ""; // Devuelve una cadena vacía si la ventana se cierra sin presionar Enter
}
