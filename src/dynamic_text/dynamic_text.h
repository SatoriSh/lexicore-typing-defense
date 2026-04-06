#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <functional>

class DynamicText
{
public:
    DynamicText(std::string text);
    ~DynamicText();

    std::function<void()> onWordCompleted;

    bool circleExplosionStarted = false;

    void inputHandler(char ch);
    void render(sf::RenderWindow& window);
    void update(sf::Vector2f position);
    float getTotalWidth();
    int getLettersCount();
private:
    const std::string fontPath = "../src/font/SansSerifFLF-DemiItalic.otf";
    const int fontSize = 30;
    const sf::Color defaultColor = {210, 205, 245};
    const sf::Color pressedColor = {0, 0, 255};

    sf::Font font;
    std::string text;
    std::vector<sf::Text> dynamicText;
    int currentStrPos = 0;
    float totalWidth = 0.0f;

    void resetAllLetters();
    void checkIfWordCompleted();
};
