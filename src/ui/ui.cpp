#include "ui.h"

UI::UI(const unsigned int screenWidth, const unsigned int screenHeight, sf::RenderWindow& window)
    : screenWidth(screenWidth), screenHeight(screenHeight), window(window), currentWaveText(font, ""), scoreText(font, "")
{
    if (!font.openFromFile(fontPath))
        printf("font opening error");

    currentWaveText.setFont(font);
    currentWaveText.setCharacterSize(90);
    
    scoreText.setFont(font);
    scoreText.setCharacterSize(90);
    scoreText.setFillColor(sf::Color::Blue);

    updateHUD(currentWave, score);
}

void UI::render()
{
    window.draw(scoreText);
}

void UI::updateHUD(int currentWave, int score)
{
    this->currentWave = currentWave;
    this->score = score;

    scoreText.setString(std::to_string(score));
    scoreText.setPosition({ screenWidth / 2 - scoreText.getLocalBounds().size.x / 2, 50 });
}

UI::~UI()
{
}
