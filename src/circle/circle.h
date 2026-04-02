#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../dynamic_text/dynamic_text.h"

class Circle
{
public:
    Circle(sf::Vector2f position, sf::Vector2f directionToHeart, std::string text); // сделать const dirToHeart
    ~Circle();

    DynamicText dynText;
    sf::CircleShape circleShape;

    bool isDestroyed = false;

    void update(float dt);
    void explode();
private:
    const sf::Color fillColor = sf::Color(42, 42, 62);
    const sf::Color outlineColor = sf::Color(90, 90, 138);
    const float radius = 30.0f;
    const float explosionMaxRadius = radius * 5;
    const float outlineThickness = 2.0f;
    const float speed = 50.0f;
    const float explosionSpeed = 650.0f;

    float currentExplosionRadius = radius;

    sf::Vector2f position;
    sf::Vector2f directionToHeart;

    bool explosionStarted = false;

    void updateOrigin();
    //sf::CircleShape glow;
};
