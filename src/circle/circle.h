#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../dynamic_text/dynamic_text.h"

class Circle
{
public:
    Circle(sf::Vector2f position, std::string text, sf::RenderWindow& window);
    ~Circle();

    void update(float dt);
    void render();
    DynamicText dynText;
private:
    const sf::Color fillColor = sf::Color(42, 42, 62);
    const sf::Color outlineColor = sf::Color(90, 90, 138);
    const float radius = 30.0f;
    const float outlineThickness = 2.0f;

    sf::Vector2f position;
    sf::CircleShape circle;
    //sf::CircleShape glow;
    sf::RenderWindow& window;
};
