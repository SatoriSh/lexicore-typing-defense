#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <memory>
#include <random>

#include "../heart/heart.h"
#include "../circle/circle.h"
#include "../dynamic_text/dynamic_text.h"

#include "../timer/timer.h"


class Game
{
public:
    Game(const unsigned int screenWidth, const unsigned int screenHeight);
    ~Game();

    void process();
private:
    const unsigned int FPS = 60;
    const std::string gameName = "LexiCore";
    const sf::Color backgroundColor = { 0, 0, 0 };
    const int screenWidth;
    const int screenHeight;
    const sf::Vector2f heartPosition;

    sf::RenderWindow window;

    Heart heart;
    std::vector<std::unique_ptr<Circle>> circles;

    sf::Clock globalClock;
    Timer timer;
    std::random_device rd;
    std::mt19937 gen;

    void spawnCircle();
    void checkCollisions();
    int getRandomValue(int min, int max);
};
