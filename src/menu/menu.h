#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Menu
{
  public:
    Menu(const unsigned int screenWidth, const unsigned int screenHeight);
    ~Menu();

    void render(sf::RenderWindow& window);

  private:
    const std::string fontPath = "../src/font/SansSerifFLF-DemiItalic.otf";
    const unsigned int screenWidth;
    const unsigned int screenHeight;
        
    sf::Font font;
    sf::Text startText;
    sf::Text continueText;
    sf::Text exitText;
};
