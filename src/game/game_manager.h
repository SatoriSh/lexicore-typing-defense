#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/System/Time.hpp>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <random>

#include "../heart/heart.h"
#include "../circle/circle.h"
#include "../dynamic_text/dynamic_text.h"
#include "../ui/ui.h"

#include "../timer/timer.h"

class Game
{
public:
    Game(sf::RenderWindow& window, int checkpoint);
    ~Game();

    std::function<void()> onEscPressed;
    std::function<void()> onMenuPressed;

    void startTimers();
    void stopTimers();

    void process();
private:
    const std::string gameName = "LexiCore";
    const sf::Color backgroundColor = {8, 6, 18} ;
    const unsigned int screenWidth;
    const unsigned int screenHeight;
    const sf::Vector2f heartPosition;
    const std::string simpleWordsPath = "../src/words/.simple_words.txt";
    const std::string mediumWordsPath = "../src/words/.medium_words.txt";
    const std::string hardWordsPath = "../src/words/.hard_words.txt";
    const std::string uniqueWordsPath = "../src/words/.unique_words.txt";
    const std::string dataPath = "../src/data/.checkpoint.txt";
    const sf::Time pauseAfterWave = sf::seconds(3);
    const sf::Time timeToSpawnCircleIfUniqueWave = sf::milliseconds(450);
    const sf::Time minTimeToSpawnCircle = sf::milliseconds(1200);
    const sf::Time maxTimeToSpawnCircle = sf::milliseconds(2000);
    const sf::Time circleSpawnDurationDecrease = sf::milliseconds(40);

    sf::RenderWindow& window;
    UI ui;

    Heart heart;
    std::vector<std::unique_ptr<Circle>> circles;

    int score = 0;
    int currentWave = 1;

    int waveDuration = 30;
    bool waveBegin = true;
    bool uniqueWave = false;
    bool stopInput = false;
    bool gameOver = false;

    sf::Clock globalClock;
    Timer circleSpawnTimer;
    Timer waveTimer;
    Timer pauseAfterWaveTimer;
    sf::Time timeToSpawnCircle = maxTimeToSpawnCircle;
    std::random_device rd;
    std::mt19937 gen;

    std::vector<std::string> simpleWords;
    std::vector<std::string> mediumWords;
    std::vector<std::string> hardWords;
    std::vector<std::string> uniqueWords;

    void initWords();
    void spawnCircle();
    void checkCollisions();
    void addScore(int v);
    void waveFinish();
    void blowUpCircles();
    void updateDifficulty();
    void saveCheckpoint();
    void skipWaves(int count);

    std::string getWordForCircle();
    int getRandomValue(int min, int max);
};
