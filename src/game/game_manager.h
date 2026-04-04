#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <memory>
#include <random>

#include "../heart/heart.h"
#include "../circle/circle.h"
#include "../dynamic_text/dynamic_text.h"
#include "../ui/ui.h"

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
    const std::string simpleWordsPath = "../src/words/.simple_words.txt";

    sf::RenderWindow window;
    UI ui;

    Heart heart;
    std::vector<std::unique_ptr<Circle>> circles;

    int score = 0;
    int currentWave = 1;

    int waveDuration = 90;

    sf::Clock globalClock;
    Timer timer;
    Timer waveTimer;
    std::random_device rd;
    std::mt19937 gen;

    std::vector<std::string> simpleWords;

    void initWords();
    void spawnCircle();
    void checkCollisions();
    void addScore(int v);
    void waveFinish();
    int getRandomValue(int min, int max);
};
