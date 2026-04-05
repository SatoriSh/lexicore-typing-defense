#include "ui.h"

UI::UI(const unsigned int screenWidth, const unsigned int screenHeight, sf::RenderWindow& window)
    :
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    window(window),
    currentWaveText(font, ""),
    scoreText(font, "")
{
    if (!font.openFromFile(fontPath))
        printf("font opening error");

    currentWaveText.setFont(font);
    currentWaveText.setCharacterSize(textCharacterSize);
    currentWaveText.setFillColor(textColor);
    currentWaveText.setPosition(currentWaveTextPos);

    scoreText.setFont(font);
    scoreText.setCharacterSize(textCharacterSize);
    scoreText.setFillColor(textColor);
    scoreText.setPosition(scoreTextPos);

    updateHUD(currentWave, score);
}

void UI::render()
{
    window.draw(currentWaveText);
    window.draw(scoreText);

    window.draw(bar.backgroundBar);
    window.draw(bar.fillBar);
}

void UI::updateHUD(int currentWave, int score)
{
    this->currentWave = currentWave;
    this->score = score;

    currentWaveText.setString(std::string("Wave: " + std::to_string(currentWave)));

    scoreText.setString(std::string("Score: ") + std::to_string(score));
}

UI::~UI()
{
}


UI::Bar::Bar()
{
    backgroundBar.setSize({ barWidth, barHeight });
    backgroundBar.setFillColor(sf::Color(0, 255, 0, 0));
    backgroundBar.setOutlineColor(sf::Color(0, 255, 0, 127));
    backgroundBar.setOutlineThickness(2.5f);


    fillBar.setSize({ barWidth, barHeight });
    fillBar.setFillColor(sf::Color(255, 0, 0, 127));
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
