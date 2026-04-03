#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <memory>

#include "heart/heart.h"
#include "circle/circle.h"
#include "dynamic_text/dynamic_text.h"

#include "timer/timer.h"

Heart heart({ 400.0f, 300.0f });

std::vector<std::unique_ptr<Circle>> circles;

void checkCollisions()
{
    for (auto& circle : circles)
    {
        if (heart.sprite.getGlobalBounds().findIntersection(circle->circleShape.getGlobalBounds()))
        {
            if (circle->isExplosionStarted())
                continue;

            circle->isHeartHitExplosion = true;
            circle->explode();
            heart.takeDamage();
        }
    }
}

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode({ desktop.size.x, desktop.size.y }), "LexiCore", sf::Style::None);
    window.setFramerateLimit(60);

    sf::Clock globalClock;

    Timer timer;
    timer.autoRestart = true;
    timer.setDuration(sf::seconds(2));

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

        //window.clear(sf::Color(26, 26, 42));
        window.clear(sf::Color(0, 0, 0));

        float dt = globalClock.restart().asSeconds();

        for (auto& circle : circles)
        {
            if (!circle->isDestroyed)
            {
                circle->update(dt);
                window.draw(circle->circleShape);
                circle->dynText.render(window);
            }
        }

        checkCollisions();

        window.draw(heart.sprite);

        window.display();
    }

    return 0;
}
