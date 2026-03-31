#include <SFML/Graphics.hpp>
#include <string>

#include "dynamic_text/DynamicText.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "LexiCore");

    DynamicText dynText(std::string("how are you"), window);

    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* textEvent = event->getIf<sf::Event::TextEntered>())
            {
                char enteredChar = static_cast<char>(textEvent->unicode);

                dynText.inputHandler(enteredChar);
            }
        }

        window.clear(sf::Color::Black);
        dynText.render();
        window.display();
    }

    return 0;
}
