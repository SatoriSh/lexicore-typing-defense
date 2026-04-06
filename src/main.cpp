#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <fstream>

#include "menu/menu.h"
#include "game/game_manager.h"

enum State
{
    MENU,
    GAME
};

State gameState = State::MENU;

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned const screenWidth = desktop.size.x;
    unsigned const screenHeight = desktop.size.y;
    unsigned const int FPS = 60;

    sf::RenderWindow window(sf::VideoMode({screenWidth, screenHeight}), "LexiCore", sf::Style::None);
    window.setFramerateLimit(FPS);

    std::unique_ptr<Game> game = nullptr;

    Menu menu(screenWidth, screenHeight);

    menu.onButtonClicked = [&](std::string button)
    {
        if (button == "start")
        {
            game = std::make_unique<Game>(window, 1); 
            gameState = State::GAME;
        }
        else if (button == "continue")
        {
            int wave = 1;
            std::ifstream file("../src/data/.checkpoint.txt");
            if (file.is_open()) {
                file >> wave;
                file.close();
            }

            game = std::make_unique<Game>(window, wave);
            gameState = State::GAME;
        }
        else if (button == "exit")
            window.close();
    };

    while (window.isOpen())
    {
        switch (gameState)
        {
        case State::MENU:
            menu.render(window);
            break;
        case State::GAME:
            game->process();
            break;
        }
    }

    return 0;
}
