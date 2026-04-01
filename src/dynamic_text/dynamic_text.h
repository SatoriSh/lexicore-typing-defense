#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class DynamicText
{
public:
    DynamicText(std::string text);
    ~DynamicText();

    void inputHandler(char ch);
    void render(sf::RenderWindow& window);
    void update(sf::Vector2f position);
private:
    const std::string fontPath = "../src/font/SansSerifFLF-DemiItalic.otf";
    const int fontSize = 20;
    const sf::Color defaultColor = sf::Color(200, 200, 232);
    const sf::Color pressedColor = sf::Color(255, 107, 107);

    sf::Font font;
    std::string text;
    std::vector<sf::Text> dynamicText;
    float totalWidth = 0.0f;
    int currentStrPos = 0;

    void resetAllLetters();
};
