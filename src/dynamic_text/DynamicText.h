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
private:
    sf::Font font;
    std::vector<sf::Text> dynamicText;
    sf::RenderWindow& window;
    const std::string fontPath = "../src/font/SansSerifFLF-DemiItalic.otf";
    const sf::Color defaultColor = sf::Color::White;
    const sf::Color pressedColor = sf::Color::Blue;
    int currentStrPos = 0;


};
