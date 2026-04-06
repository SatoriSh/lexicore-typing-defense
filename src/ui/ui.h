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
    void renderNextWaveAnim(float dt);
    void resetAnimState();

    struct Bar
    {
    public:
        Bar();
        ~Bar();

        void setMaxWidth(float v);
        void updateWidth(float v);
        void setPosition(sf::Vector2f position);

        sf::RectangleShape backgroundBar;
        sf::RectangleShape fillBar;

      private:
        const sf::Color backgroundBarOutlineColor = {70, 60, 110, 190};
        const sf::Color backgroundBarFillColor = {70, 60, 110, 40};
        const sf::Color fillBarColor = {200, 55, 75, 210};
        const float barHeight = 30;
        const int widthMultiplier = 5;
        float barWidth;
        float fillBarWidth;
    };

    Bar bar;
private:
    const unsigned int screenWidth;
    const unsigned int screenHeight;
    const std::string fontPath = "../src/font/SansSerifFLF-DemiItalic.otf";
    const float textCharacterSize = 35.0f;
    const sf::Color textColor = {170, 150, 255};
    const sf::Vector2f currentWaveTextPos = { 30, 30 };
    const sf::Vector2f scoreTextPos = { 30, 75 };
    const float transparencyChangingSpeed = 180.0f;

    sf::RenderWindow& window;

    int currentWave = 1;
    int score = 0;

    float transparency = 0.0f;
    bool isNextWaveAnimFadeIn = true;
    bool isNextWaveAnimFinish = false;

    sf::Font font;
    sf::Text currentWaveText;
    sf::Text scoreText;
    sf::Text nextWaveAnimText;
};
