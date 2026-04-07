#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "../dynamic_text/dynamic_text.h"

class Circle
{
public:
    Circle(sf::Vector2f position, const sf::Vector2f directionToHeart, std::string text);
    ~Circle();

    DynamicText dynText;
    sf::CircleShape circleShape;

    bool isDestroyed = false;
    bool isHeartHitExplosion = false;

    std::function<void(int)> addScore;
    std::function<void()> onExplodeSuccess;

    void update(float dt);
    void explode();
    bool isExplosionStarted();
private:
    const sf::Vector2f directionToHeart;
    const sf::Color fillColor = {30, 25, 55};
    const sf::Color outlineColor = {110, 85, 200};
    const float outlineThickness = 2.0f;
    const float explosionSpeed = 650.0f;
    const size_t pointCount = 200;
    const size_t pointCountAfterExplosion = 1000; // updating the number of points, since the larger the circle, the more points are needed for detail
    const float minSpeed = 80.0f;
    const float minTransparencyChangingSpeed = 400.0f;
    const int scoreMultiplier = 5;

    float radius = 0.0f;
    float speed = 200.0f;
    float transparency = 200.0f;
    float transparencyChangingSpeed = 550.0f;

    sf::Vector2f position;

    bool explosionStarted = false;

    void updateOrigin();
};
