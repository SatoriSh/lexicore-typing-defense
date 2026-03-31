#include <SFML/Graphics.hpp>
#include <string>

#include "circle/circle.h"
#include "dynamic_text/dynamic_text.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "LexiCore");

    Circle circle({400.0f,300.0f}, std::string("circle"), window);

    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* textEvent = event->getIf<sf::Event::TextEntered>())
            {
                char enteredChar = static_cast<char>(textEvent->unicode);

                circle.dynText.inputHandler(enteredChar);
            }
        }

        window.clear(sf::Color(26, 26, 42));
        circle.update();
        window.display();
    }

    return 0;
}
