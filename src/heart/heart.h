#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Heart
{
public:
    Heart(sf::Vector2f position);
    ~Heart();

    std::function<void()> onDead;

    void takeDamage();
    void addLife();
    void fullHeal();

    sf::Sprite sprite;
private:
    const char* texturePath = "../src/sprites/hearts.png";
    const int maxHealth = 4;

    int health = maxHealth;
    sf::Texture texture;

    sf::IntRect heartRects[5];
};
