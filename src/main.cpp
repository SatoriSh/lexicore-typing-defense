#include <SFML/Graphics.hpp>
#include <string>

#include "heart/heart.h"
#include "circle/circle.h"
#include "dynamic_text/dynamic_text.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "LexiCore");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Heart heart({ 400.0f, 300.0f });

    sf::Vector2f directionToHeart = sf::Vector2f{ 400.0f, 300.0f } - sf::Vector2f{ 100.0f, 100.0f };
    directionToHeart = directionToHeart.normalized();
    Circle circle({ 100.0f,100.0f }, directionToHeart, std::string("circLe"));

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

        float dt = clock.restart().asSeconds();
        circle.update(dt);

        window.draw(circle.circle);
        circle.dynText.render(window);
        window.draw(heart.sprite);

        window.display();
    }

    return 0;
}
