#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

Menu::Menu(const unsigned int screenWidth, const unsigned int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), startText(font, ""),
      continueText(font, ""), exitText(font, ""), pauseContinueText(font, ""),
      pauseOpenMenuText(font, "")
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
    continueText.setString("[C]    Continue from the checkpoint");
    exitText.setString("[E]     Exit");

    startText.setFillColor(textColor);
    continueText.setFillColor(textColor);
    exitText.setFillColor(textColor);

    float offsetY = startText.getLocalBounds().size.y + continueText.getLocalBounds().size.y + exitText.getLocalBounds().size.y;
    float startY = (float)screenHeight / 4 + offsetY / 2;

    startText.setPosition({(float)screenWidth / 2 - startText.getLocalBounds().size.x / 2, startY});

    startY += (float)screenHeight / 12;
    continueText.setPosition({(float)screenWidth / 2 - continueText.getLocalBounds().size.x / 2, startY});

    startY += (float)screenHeight / 12;
    exitText.setPosition( {(float)screenWidth / 2 - exitText.getLocalBounds().size.x / 2, startY});

    pauseContinueText.setFont(font);
    pauseOpenMenuText.setFont(font);

    pauseContinueText.setCharacterSize(64);
    pauseOpenMenuText.setCharacterSize(64);

    pauseContinueText.setString("[C]    Continue");
    pauseOpenMenuText.setString("[M]    Open Menu");

    pauseContinueText.setFillColor(textColor);
    pauseOpenMenuText.setFillColor(textColor);

    offsetY = pauseContinueText.getLocalBounds().size.y + pauseOpenMenuText.getLocalBounds().size.y;
    startY = (float)screenHeight / 4 + offsetY;

    pauseContinueText.setPosition({(float)screenWidth / 2 - pauseContinueText.getLocalBounds().size.x / 2, startY});

    startY += (float)screenHeight / 12;
    pauseOpenMenuText.setPosition( {(float)screenWidth / 2 - pauseOpenMenuText.getLocalBounds().size.x / 2, startY});
}

void Menu::render(sf::RenderWindow& window)
{
    pause = false;
    buttonClicked = false;

    while (!buttonClicked)
    {
        inputHandler();

        window.clear({0,0,0});
        window.draw(startText);
        window.draw(continueText);
        window.draw(exitText);
        window.display();
    }
}

void Menu::pauseRender(sf::RenderWindow &window)
{
    pause = true;
    buttonClicked = false;

    while (!buttonClicked)
    {   
        inputHandler();

        window.clear({0,0,0});
        window.draw(pauseContinueText);
        window.draw(pauseOpenMenuText);
        window.display();
    }
}

void Menu::inputHandler()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !pause)
    {
        onButtonClicked("start");
        buttonClicked = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) && !pause)
    {
        onButtonClicked("checkpoint_continue");
        buttonClicked = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) && pause)
    {
        onButtonClicked("pause_continue");
        buttonClicked = true;
        pause = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && pause)
    {
        onButtonClicked("open_menu");
        buttonClicked = true;
        pause = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && !pause)
    {
        onButtonClicked("exit");
        buttonClicked = true;
    }
}

Menu::~Menu()
{
}
