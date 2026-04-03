#include "dynamic_text.h"

DynamicText::DynamicText(std::string text)
{
    if (!font.openFromFile(fontPath))
        printf("font opening error");

    for (char& c : text)
    {
        sf::Text tempText(font, c);
        tempText.setFillColor(defaultColor);
        tempText.setCharacterSize(fontSize);
        tempText.setPosition({ 0, 0 });

        totalWidth += tempText.getLocalBounds().size.x;
        dynamicText.push_back(tempText);
    }
}

void DynamicText::update(sf::Vector2f position)
{
    float x = position.x - totalWidth / 1.75;
    float y = position.y - fontSize / 1.3;

    for (sf::Text& t : dynamicText)
    {
        t.setPosition({ x, y });

        sf::Glyph g = font.getGlyph(t.getString()[0], fontSize, false);
        x += g.advance;
    }
}

void DynamicText::inputHandler(char ch)
{
    if (circleExplosionStarted)
        return;

    for (int i = 0; i < dynamicText.size(); i++)
    {
        if (i == currentStrPos)
        {
            if (ch == dynamicText[i].getString()[0])
            {
                dynamicText[i].setFillColor(pressedColor);
                currentStrPos++;
                break;
            }
            else if (ch != dynamicText[i].getString()[0])
                resetAllLetters();
        }
    }

    checkIfWordCompleted();
}

void DynamicText::render(sf::RenderWindow& window)
{
    if (circleExplosionStarted)
        return;

    for (sf::Text& ch : dynamicText)
    {
        window.draw(ch);
    }
}

void DynamicText::checkIfWordCompleted()
{
    for (sf::Text& t : dynamicText)
        if (t.getFillColor() != pressedColor) return;

    onWordCompleted();
}

void DynamicText::resetAllLetters()
{
    for (sf::Text& t : dynamicText)
        t.setFillColor(defaultColor);

    currentStrPos = 0;
}

float DynamicText::getTotalWidth() { return totalWidth; };

DynamicText::~DynamicText()
{
}
