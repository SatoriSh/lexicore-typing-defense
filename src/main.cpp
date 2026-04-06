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
    GAME,
    PAUSE
};

State gameState = State::MENU;

std::unique_ptr<Game> game = nullptr;

void initGame(sf::RenderWindow& window, int wave)
{
    game = std::make_unique<Game>(window, wave);

    game->onEscPressed = [&]()
    {
        gameState = State::PAUSE;
    };
}

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned const screenWidth = desktop.size.x;
    unsigned const screenHeight = desktop.size.y;
    unsigned const int FPS = 60;

    sf::RenderWindow window(sf::VideoMode({screenWidth, screenHeight}), "LexiCore", sf::Style::None);
    window.setFramerateLimit(FPS);

    Menu menu(screenWidth, screenHeight);

    menu.onButtonClicked = [&](std::string button)
    {
        if (button == "start")
        {
            initGame(window, 1);
            gameState = State::GAME;
        }
        else if (button == "checkpoint_continue")
        {
            int wave = 1;
            std::ifstream file("../src/data/.checkpoint.txt");
            if (file.is_open()) {
                file >> wave;
                file.close();
            }

            initGame(window, wave);
            gameState = State::GAME;
        }
        else if (button == "pause_continue")
        {
            game->startTimers();
            gameState = State::GAME;
        }
        else if (button == "open_menu")
        {
            gameState = State::MENU;
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
        case State::PAUSE:
            menu.pauseRender(window);
            break;
        }
    }

    return 0;
}
