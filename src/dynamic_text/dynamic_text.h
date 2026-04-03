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
    const sf::Color defaultColor = sf::Color(200, 200, 232);
    const sf::Color pressedColor = sf::Color(255, 107, 107);

    sf::Font font;
    std::string text;
    std::vector<sf::Text> dynamicText;
    int currentStrPos = 0;
    float totalWidth = 0.0f;

    void resetAllLetters();
    void checkIfWordCompleted();
};
