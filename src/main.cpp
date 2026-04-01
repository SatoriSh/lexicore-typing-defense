#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <memory>

#include "heart/heart.h"
#include "circle/circle.h"
#include "dynamic_text/dynamic_text.h"

#include "timer/timer.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "LexiCore");
    window.setFramerateLimit(60);

    sf::Clock globalClock;

    Timer timer;
    timer.autoRestart = true;
    timer.setDuration(sf::seconds(2));

    Heart heart({ 400.0f, 300.0f });

    std::vector<std::unique_ptr<Circle>> circles;

    sf::Vector2f directionToHeart = sf::Vector2f{ 400.0f, 300.0f } - sf::Vector2f{ 100.0f, 100.0f };
    directionToHeart = directionToHeart.normalized();

    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* textEvent = event->getIf<sf::Event::TextEntered>())
            {
                char enteredChar = static_cast<char>(textEvent->unicode);

                for (auto& circle : circles)
                {
                    circle->dynText.inputHandler(enteredChar);
                }
            }
        }

        if (timer.timeout())
        {
            circles.push_back(std::make_unique<Circle>(sf::Vector2f{ 100.0f,100.0f }, directionToHeart, std::string("circle")));
        }

        window.clear(sf::Color(26, 26, 42));

        float dt = globalClock.restart().asSeconds();

        for (auto& circle : circles)
        {
            circle->update(dt);
            window.draw(circle->circle);
            circle->dynText.render(window);
        }

        window.draw(heart.sprite);

        window.display();
    }

    return 0;
}
