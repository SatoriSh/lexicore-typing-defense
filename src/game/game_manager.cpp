#include "game_manager.h"

#include <fstream>

Game::Game(const unsigned int screenWidth, const unsigned int screenHeight)
    :
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    heartPosition({ (float)screenWidth / 2, (float)screenHeight / 2 }),
    heart(heartPosition),
    window(sf::VideoMode({ screenWidth, screenHeight }), gameName, sf::Style::None),
    ui(screenWidth, screenHeight, window),
    gen(rd())
{
    window.setFramerateLimit(FPS);

    timer.autoRestart = true;
    timer.setDuration(sf::milliseconds(1000));

    waveTimer.autoRestart = true;
    waveTimer.setDuration(sf::seconds(waveDuration));

    pauseAfterWaveTimer.setDuration(sf::seconds(pauseAfterWave));
    pauseAfterWaveTimer.autoRestart = false;
    pauseAfterWaveTimer.getClock().stop();

    ui.bar.setMaxWidth(waveDuration);
    ui.bar.setPosition({ screenWidth / 2 - ui.bar.backgroundBar.getLocalBounds().size.x / 2, 30 });

    initWords();
}

void Game::process()
{
    // Timer timerFPS;
    // timerFPS.autoRestart = true;
    // timerFPS.setDuration(sf::milliseconds(500));

    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* textEvent = event->getIf<sf::Event::TextEntered>())
            {
                char enteredChar = static_cast<char>(textEvent->unicode);

                for (auto& circle : circles)
                {
                    circle->dynText.inputHandler(enteredChar);
                }
            }
        }

        ui.bar.updateWidth(waveTimer.getLeftTime().asSeconds());

        if (timer.timeout() && waveBegin)
        {
            spawnCircle();
        }
        if (waveTimer.timeout())
        {
            waveFinish();
        }
        if (pauseAfterWaveTimer.timeout())
        {
            pauseAfterWaveTimer.getClock().reset();
            circles.clear();
            ui.resetAnimState();
            waveBegin = true;
        }

        window.clear(backgroundColor);

        float dt = globalClock.restart().asSeconds();

        for (auto& circle : circles)
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

        if (!waveBegin)
            ui.renderNextWaveAnim(dt);

        window.display();

        // if (timerFPS.timeout())
        // {
        //     printf("%f ", 1.f / dt);
        // }
    }
}

void Game::waveFinish()
{
    currentWave++;
    ui.updateHUD(currentWave, score);
    blowUpCircles();

    waveBegin = false;
    pauseAfterWaveTimer.getClock().start();
}

void Game::spawnCircle()
{
    std::string word = simpleWords.at(getRandomValue(0, simpleWords.size() - 1));
    float offset = word.size() * 12;

    sf::Vector2f spawnPosition;
    int spawnSide = getRandomValue(1, 4);

    switch (spawnSide)
    {
    case 1:  // up
        spawnPosition = { (float)getRandomValue(0, screenWidth), -offset };
        break;
    case 2: // right
        spawnPosition = { (float)screenWidth + offset, (float)getRandomValue(0, screenHeight) };
        break;
    case 3: // down
        spawnPosition = { (float)getRandomValue(0, screenWidth), (float)screenHeight + offset };
        break;
    case 4: // left
        spawnPosition = { -offset, (float)getRandomValue(0, screenHeight) };
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
    for (auto& circle : circles)
    {
        if (heart.sprite.getGlobalBounds().findIntersection(circle->circleShape.getGlobalBounds()))
        {
            if (circle->isExplosionStarted())
                continue;

            circle->isHeartHitExplosion = true;
            circle->explode();
            heart.takeDamage();
        }
    }
}

void Game::blowUpCircles()
{
    for (auto& circle : circles)
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
    std::ifstream simpleWordsFile(simpleWordsPath);

    std::string word;

    while (simpleWordsFile >> word)
        simpleWords.push_back(word);
}

int Game::getRandomValue(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

Game::~Game()
{
}
