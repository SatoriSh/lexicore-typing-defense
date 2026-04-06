#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "menu/menu.h"
#include "game/game_manager.h"

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned const screenWidth = desktop.size.x;
    unsigned const screenHeight = desktop.size.y;
    unsigned const int FPS = 60;

    sf::RenderWindow window(sf::VideoMode({screenWidth, screenHeight}), "LexiCore", sf::Style::None);
    window.setFramerateLimit(FPS);

    Menu menu(screenWidth, screenHeight);
    menu.render(window);

    Game game(window);
    game.process();

    return 0;
}
