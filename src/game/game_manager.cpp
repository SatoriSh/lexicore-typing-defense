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

        if (timer.timeout())
        {
            spawnCircle();
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

        window.display();

        // if (timerFPS.timeout())
        // {
        //     printf("%f ", 1.f / dt);
        // }
    }
}

void Game::spawnCircle()
{
    sf::Vector2f spawnPosition;
    int spawnSide = getRandomValue(1, 4);

    float offset = 100;

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

    std::string word = simpleWords.at(getRandomValue(0, simpleWords.size() - 1));

    std::unique_ptr<Circle> circle = std::make_unique<Circle>(spawnPosition, directionToHeart, word);

    circle->addScore = [this](int v) { addScore(v); };

    circles.push_back(std::move(circle));
}

int Game::getRandomValue(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
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

void Game::addScore(int v)
{
    score += v;
    ui.updateHUD(0, score);
}

void Game::initWords()
{
    std::ifstream simpleWordsFile("../src/words/.simple_words.txt");

    std::string word;

    while (simpleWordsFile >> word)
        simpleWords.push_back(word);
}

Game::~Game()
{
}
