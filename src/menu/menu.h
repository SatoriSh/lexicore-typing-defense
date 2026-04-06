#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <functional>

class Menu
{
  public:
    Menu(const unsigned int screenWidth, const unsigned int screenHeight);
    ~Menu();

    void render(sf::RenderWindow &window);
    void pauseRender(sf::RenderWindow &window);
    std::function<void(std::string button)> onButtonClicked;

  private:
    const std::string fontPath = "../src/font/SansSerifFLF-DemiItalic.otf";
    const unsigned int fontSize = 64;
    const unsigned int screenWidth;
    const unsigned int screenHeight;
    const sf::Color textColor = {170, 150, 255};

    bool buttonClicked = false;
    bool pause = false;

    void inputHandler();

    sf::Font font;
    sf::Text startText;
    sf::Text continueText;
    sf::Text exitText;

    sf::Text pauseContinueText;
    sf::Text pauseOpenMenuText;
};
