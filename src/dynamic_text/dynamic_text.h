#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class DynamicText
{
public:
    DynamicText(std::string text, sf::RenderWindow& window);
    ~DynamicText();

    void inputHandler(char ch);
    void render();
    void update(sf::Vector2f position);
private:
    const std::string fontPath = "../src/font/SansSerifFLF-DemiItalic.otf";
    const int fontSize = 20;
    const sf::Color defaultColor = sf::Color::White;
    const sf::Color pressedColor = sf::Color::Blue;

    sf::Font font;
    std::string text;
    std::vector<sf::Text> dynamicText;
    sf::RenderWindow& window;
    int currentStrPos = 0;

    void resetAllLetters();
};
