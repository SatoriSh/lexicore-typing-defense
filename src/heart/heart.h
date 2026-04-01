#pragma once

#include <SFML/Graphics.hpp>

class Heart
{
public:
    Heart(sf::Vector2f position);
    ~Heart();

    sf::Sprite sprite;
private:
    const char* texturePath = "../src/sprites/hearts.png";
    const int maxHealth = 4;
    int currentHealth = maxHealth;
    sf::Texture texture;
};
