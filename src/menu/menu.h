#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Menu
{
  public:
    Menu(const unsigned int screenWidth, const unsigned int screenHeight);
    ~Menu();

    void render(sf::RenderWindow &window);
    std::function<void(std::string button)> onButtonClicked;

  private:
    const std::string fontPath = "../src/font/SansSerifFLF-DemiItalic.otf";
    const unsigned int screenWidth;
    const unsigned int screenHeight;

    bool buttonClicked = false;

    void inputHandler();

    sf::Font font;
    sf::Text startText;
    sf::Text continueText;
    sf::Text exitText;
};
