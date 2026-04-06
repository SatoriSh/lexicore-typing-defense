#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include "game_manager.h"

Game::Game(sf::RenderWindow &window, int checkpoint)
    : window(window),
      screenWidth(window.getSize().x), screenHeight(window.getSize().y),
      heartPosition({(float)screenWidth / 2, (float)screenHeight / 2}),
      heart(heartPosition),
      ui(screenWidth, screenHeight, window), gen(rd())
{
    circleSpawnTimer.autoRestart = true;
    circleSpawnTimer.setDuration(timeToSpawnCircle);

    waveTimer.autoRestart = false;
    waveTimer.setDuration(sf::seconds(waveDuration));

    pauseAfterWaveTimer.setDuration(pauseAfterWave);
    pauseAfterWaveTimer.autoRestart = false;
    pauseAfterWaveTimer.getClock().stop();

    ui.bar.setMaxWidth(waveDuration);
    ui.bar.setPosition({(float)screenWidth / 2 - ui.bar.backgroundBar.getLocalBounds().size.x / 2, 30});

    if (checkpoint > 1)
    {
        skipWaves(checkpoint);
    }

    ui.updateHUD(currentWave, score);
    initWords();
}

void Game::process()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        stopTimers();
        onEscPressed();
    }

    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto *textEvent = event->getIf<sf::Event::TextEntered>())
        {   
            char enteredChar = static_cast<char>(textEvent->unicode);

            for (auto &circle : circles)
            {
                circle->dynText.inputHandler(enteredChar);
            }
        }
    }

    if (waveBegin)
        ui.bar.updateWidth(waveTimer.getLeftTime().asSeconds());

    if (waveBegin && circleSpawnTimer.timeout())
    {
        spawnCircle();
    }
    if (waveBegin && waveTimer.timeout())
    {
        waveFinish();
    }
    if (!waveBegin && pauseAfterWaveTimer.timeout())
    {
        pauseAfterWaveTimer.getClock().reset();
        circles.clear();
        updateDifficulty();
        
        waveTimer.getClock().restart();
        waveBegin = true;
    }

    window.clear(backgroundColor);

    float dt = globalClock.restart().asSeconds();
    if (dt > 0.1f) dt = 1.0f / 60.0f;

    for (auto &circle : circles)
    {
        if (!circle->isDestroyed)
        {
            circle->update(dt);
            window.draw(circle->circleShape);
            circle->dynText.render(window);
        }
    }

    checkCollisions();

    window.draw(heart.sprite);

    ui.render();

    ui.renderNextWaveAnim(dt);

    window.display();
}

void Game::waveFinish()
{
    if (uniqueWave)
    {
        saveCheckpoint();
        heart.fullHeal();
    }

    currentWave++;
    uniqueWave = currentWave % 5 == 0 ? true : false;

    ui.updateHUD(currentWave, score);
    blowUpCircles();

    waveBegin = false;
    ui.resetAnimState();
    pauseAfterWaveTimer.getClock().restart();
}

void Game::updateDifficulty()
{
    timeToSpawnCircle -= circleSpawnDurationDecrease;
    if (timeToSpawnCircle < minTimeToSpawnCircle)
        timeToSpawnCircle = minTimeToSpawnCircle;

    if (uniqueWave)
        timeToSpawnCircle = timeToSpawnCircleIfUniqueWave;

    circleSpawnTimer.setDuration(timeToSpawnCircle);
}

void Game::spawnCircle()
{
    std::string word = getWordForCircle();
    float offset = word.size() * 12;

    sf::Vector2f spawnPosition;

    int spawnSide = getRandomValue(1, 4);
    switch (spawnSide)
    {
    case 1: // up
        spawnPosition = {(float)getRandomValue(0, screenWidth), -offset};
        break;
    case 2: // right
        spawnPosition = {(float)screenWidth + offset,
                         (float)getRandomValue(0, screenHeight)};
        break;
    case 3: // down
        spawnPosition = {(float)getRandomValue(0, screenWidth),
                         (float)screenHeight + offset};
        break;
    case 4: // left
        spawnPosition = {-offset, (float)getRandomValue(0, screenHeight)};
        break;
    }

    sf::Vector2f directionToHeart = heartPosition - spawnPosition;
    directionToHeart = directionToHeart.normalized();

    std::unique_ptr<Circle> circle = std::make_unique<Circle>(spawnPosition, directionToHeart, word);
    circle->addScore = [this](int v) { addScore(v); };

    circles.push_back(std::move(circle));
}

void Game::checkCollisions()
{
    for (auto &circle : circles)
    {
        if (heart.sprite.getGlobalBounds().findIntersection(
                circle->circleShape.getGlobalBounds()))
        {
            if (circle->isExplosionStarted())
                continue;

            circle->isHeartHitExplosion = true;
            circle->explode();
            heart.takeDamage();
        }
    }
}

void Game::saveCheckpoint()
{
    int checkpoint = 0;
    int dataCheckpoint = 0;

    std::fstream dataFile(dataPath);

    if (dataFile.is_open())
    {
        dataFile >> checkpoint;
    }

    if (currentWave < checkpoint)
        return;

    std::ofstream file(dataPath, std::ios::trunc);

    if (file.is_open()) {
        file << currentWave;
        file.close();
    }
}

std::string Game::getWordForCircle()
{
    if (uniqueWave)
    {
        return uniqueWords.at(getRandomValue(0, uniqueWords.size() - 1));
    }
    else
    {
        if (currentWave <= 5 && simpleWords.size() > 0)
            return simpleWords.at(getRandomValue(0, simpleWords.size() - 1));
        else if (currentWave <= 10 && mediumWords.size() > 0)
            return mediumWords.at(getRandomValue(0, mediumWords.size() - 1));
        else if (hardWords.size() > 0)
            return hardWords.at(getRandomValue(0, hardWords.size() - 1));
    }

    return "?";
}

void Game::skipWaves(int count)
{
    for (int i = 0; i < count; i++)
    {
        currentWave++;
        updateDifficulty();
    }
    waveBegin = true;
}

void Game::blowUpCircles()
{
    for (auto &circle : circles)
    {
        if (!circle->isDestroyed)
        {
            circle->explode();
        }
    }
}

void Game::addScore(int v)
{
    score += v;
    ui.updateHUD(currentWave, score);
}

void Game::initWords()
{
    std::string word;

    std::ifstream simpleWordsFile(simpleWordsPath);
    while (simpleWordsFile >> word)
        simpleWords.push_back(word);

    std::ifstream mediumWordsFile(mediumWordsPath);
    while (mediumWordsFile >> word)
        mediumWords.push_back(word);

    std::ifstream hardWordsFile(hardWordsPath);
    while (hardWordsFile >> word)
        hardWords.push_back(word);

    std::ifstream uniqueWordsFile(uniqueWordsPath);
    while (uniqueWordsFile >> word)
        uniqueWords.push_back(word);
}

void Game::startTimers()
{   
    while (window.pollEvent()); // clear buffer
    
    circleSpawnTimer.getClock().start();
    waveTimer.getClock().start();
    pauseAfterWaveTimer.getClock().start();
    globalClock.restart();

    stopInput = false;
}

void Game::stopTimers()
{
    circleSpawnTimer.getClock().stop();
    waveTimer.getClock().stop();
    pauseAfterWaveTimer.getClock().stop();
    globalClock.stop();

    stopInput = true;
}

int Game::getRandomValue(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

Game::~Game()
{
}
