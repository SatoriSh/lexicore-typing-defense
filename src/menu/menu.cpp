#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

Menu::Menu(const unsigned int screenWidth, const unsigned int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), startText(font, ""), continueText(font, ""), exitText(font, "")
{
    if (!font.openFromFile(fontPath))
        printf("font opening error");

    startText.setFont(font);
    continueText.setFont(font);
    exitText.setFont(font);

    startText.setCharacterSize(64);
    continueText.setCharacterSize(64);
    exitText.setCharacterSize(64);

    startText.setString("[S]    Start");
    continueText.setString("[C]    Continue last checkpoint");
    exitText.setString("[E]     Exit");

    startText.setFillColor({0,0,255});
    continueText.setFillColor({0,0,255});
    exitText.setFillColor({0,0,255});

    float startY = (float)screenHeight / 4;

    startText.setPosition({(float)screenWidth / 2 - startText.getLocalBounds().size.x / 2, startY});

    startY += (float)screenHeight / 10;
    continueText.setPosition({(float)screenWidth / 2 - continueText.getLocalBounds().size.x / 2, startY});

    startY += (float)screenHeight / 10;
    exitText.setPosition({(float)screenWidth / 2 - exitText.getLocalBounds().size.x / 2, startY});
}

void Menu::render(sf::RenderWindow& window)
{
    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) ||
           !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) ||
           !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        window.clear({0,0,0});

        window.draw(startText);
        window.draw(continueText);
        window.draw(exitText);

        window.display();
    }
}

Menu::~Menu()
{
}
