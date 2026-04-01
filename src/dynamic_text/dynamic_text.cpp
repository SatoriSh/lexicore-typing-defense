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
    float x = position.x - totalWidth / 2;
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
}

void DynamicText::render(sf::RenderWindow& window)
{
    for (sf::Text& c : dynamicText)
    {
        window.draw(c);
    }
}

void DynamicText::resetAllLetters()
{
    for (sf::Text& t : dynamicText)
        t.setFillColor(defaultColor);

    currentStrPos = 0;
}

DynamicText::~DynamicText()
{
}
