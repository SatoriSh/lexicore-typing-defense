#include "ui.h"
#include <SFML/Graphics/Color.hpp>
#include <cstdint>
#include <string>

UI::UI(const unsigned int screenWidth, const unsigned int screenHeight, sf::RenderWindow& window)
    :
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    window(window),
    currentWaveText(font, ""),
    scoreText(font, ""),
    nextWaveAnimText(font, ""),
    gameOverText(font, "")
{
    if (!font.openFromFile(fontPath))
        printf("font opening error");

    currentWaveText.setFont(font);
    currentWaveText.setCharacterSize(waveTextFontSize);
    currentWaveText.setFillColor(textColor);
    currentWaveText.setPosition(currentWaveTextPos);

    scoreText.setFont(font);
    scoreText.setCharacterSize(scoreTextFontSize);
    scoreText.setFillColor(textColor);
    scoreText.setPosition(scoreTextPos);

    nextWaveAnimText.setFont(font);
    nextWaveAnimText.setCharacterSize(nextWaveAnimTextFontSize);

    updateHUD(currentWave, score);

    rectangle.setSize({(float)screenWidth, (float)screenHeight});
    rectangle.setOrigin({rectangle.getLocalBounds().size.x / 2, rectangle.getLocalBounds().size.y / 2});
    rectangle.setPosition({(float)screenWidth / 2, (float)screenHeight / 2});

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(gameOverTextFontSize);
    gameOverText.setString(gameOverTextString);
    gameOverTextPos = {(float)screenWidth / 2 - gameOverText.getLocalBounds().size.x / 2, (float)screenHeight / 2 - gameOverText.getLocalBounds().size.y / 1.8f};
    gameOverText.setPosition(gameOverTextPos);
}

void UI::render()
{
    window.draw(currentWaveText);
    window.draw(scoreText);

    window.draw(bar.backgroundBar);
    window.draw(bar.fillBar);
}

void UI::renderNextWaveAnim(float dt)
{
    if (isNextWaveAnimFinish)
        return;

    nextWaveAnimText.setPosition({ (float)screenWidth / 2 - nextWaveAnimText.getLocalBounds().size.x / 2, 200 });

    if (isNextWaveAnimFadeIn)
    {
        nextWaveAnimTextTransparency += transparencyChangingSpeed * dt;
        if (nextWaveAnimTextTransparency > 255)
        {
            nextWaveAnimTextTransparency = 255;
            isNextWaveAnimFadeIn = false;
        }
    }
    else
    {
        nextWaveAnimTextTransparency -= transparencyChangingSpeed * dt;
        if (nextWaveAnimTextTransparency < 0)
        {
            nextWaveAnimTextTransparency = 0;
            isNextWaveAnimFadeIn = true;
            isNextWaveAnimFinish = true;
        }
    }

    nextWaveAnimText.setFillColor(sf::Color{ 255, 190, 40, (uint8_t)nextWaveAnimTextTransparency });

    window.draw(nextWaveAnimText);
}

void UI::renderGameOverAnim(float dt)
{
    gameOverScreenTransparency += transparencyChangingSpeed * dt;
    if (gameOverScreenTransparency > 255)
        gameOverScreenTransparency = 255;

    sf::Color rectangleColor = {0, 0, 0, (uint8_t)gameOverScreenTransparency};
    sf::Color gameOverTextColor = {255,0,0, (uint8_t)gameOverScreenTransparency};

    rectangle.setFillColor(rectangleColor);
    gameOverText.setFillColor(gameOverTextColor);

    window.draw(rectangle);
    window.draw(gameOverText);
}

void UI::updateHUD(int currentWave, int score)
{
    this->currentWave = currentWave;
    this->score = score;

    currentWaveText.setString(std::string("Wave: " + std::to_string(currentWave)));
    scoreText.setString(std::string("Score: ") + std::to_string(score));

    std::string checkpoint = currentWave % 5 == 0 ? " (checkpoint)" : "";
    nextWaveAnimText.setString(std::string("Wave " + std::to_string(currentWave) + checkpoint));
}

void UI::resetAnimState()
{
    isNextWaveAnimFinish = false; 
    isNextWaveAnimFadeIn = true; 
    nextWaveAnimTextTransparency = 0.0f;
};

UI::~UI()
{
}


UI::Bar::Bar()
{
    backgroundBar.setSize({ barWidth, barHeight });
    backgroundBar.setFillColor(backgroundBarFillColor);
    backgroundBar.setOutlineColor(backgroundBarOutlineColor);
    backgroundBar.setOutlineThickness(2.5f);

    fillBar.setSize({ barWidth, barHeight });
    fillBar.setFillColor(fillBarColor);
}

void UI::Bar::setMaxWidth(float v)
{
    barWidth = v * widthMultiplier;
    backgroundBar.setSize({ barWidth, barHeight });
};

void UI::Bar::updateWidth(float v)
{
    fillBarWidth = v * widthMultiplier;
    fillBar.setSize({ fillBarWidth, barHeight });
};

void UI::Bar::setPosition(sf::Vector2f position)
{
    backgroundBar.setPosition(position);
    fillBar.setPosition(position);
}

UI::Bar::~Bar()
{
}
