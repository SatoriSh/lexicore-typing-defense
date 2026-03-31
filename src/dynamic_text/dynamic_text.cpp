#include "dynamic_text.h"

DynamicText::DynamicText(std::string text, sf::RenderWindow& window)
    : window(window)
{
    if (!font.openFromFile(fontPath))
        printf("font opening error");

    float startX = 0.0f;
    for (char& c : text)
    {
        sf::Glyph g = font.getGlyph(c, fontSize, false);

        sf::Text tempText(font, c);
        tempText.setFillColor(sf::Color::White);
        tempText.setCharacterSize(fontSize);
        tempText.setPosition({ startX, 0 });

        startX += g.advance;

        dynamicText.push_back(tempText);
    }
}

void DynamicText::update(sf::Vector2f position)
{
    float startX = position.x;
    for (sf::Text& t : dynamicText)
    {
        t.setPosition({ startX, position.y });

        sf::Glyph g = font.getGlyph(t.getString()[0], fontSize, false);
        startX += g.advance;
    }

    render();
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

void DynamicText::render()
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
