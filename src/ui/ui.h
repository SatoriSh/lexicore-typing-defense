#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class UI
{
public:
    UI(const unsigned int screenWidth, const unsigned int screenHeight, sf::RenderWindow& window);
    ~UI();

    void updateHUD(int currentWave, int score);

    void render();
private:
    const unsigned int screenWidth;
    const unsigned int screenHeight;
    const std::string fontPath = "../src/font/SansSerifFLF-DemiItalic.otf";

    sf::RenderWindow& window;

    int currentWave = 0;
    int score = 0;

    sf::Font font;
    sf::Text currentWaveText;
    sf::Text scoreText;
};
