#include <SFML/Graphics.hpp>
#include "game/game_manager.h"

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    Game game(desktop.size.x, desktop.size.y);

    game.process();

    return 0;
}
