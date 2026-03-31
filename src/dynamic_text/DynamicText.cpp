#include "DynamicText.h"

DynamicText::DynamicText(std::string text, sf::RenderWindow& window)
    : window(window)
{
    if (!font.openFromFile(fontPath))
        printf("font opening error");

    float startX = 400.0f;
    for (char& c : text)
    {
        sf::Glyph g = font.getGlyph(c, 20, false);

        sf::Text tempText(font, c);
        tempText.setFillColor(sf::Color::White);
        tempText.setCharacterSize(20);
        tempText.setPosition({ startX, 300 });

        startX += g.advance;

        dynamicText.push_back(tempText);
    }
}

void DynamicText::render()
{
    for (sf::Text& c : dynamicText)
    {
        window.draw(c);
    }
}

DynamicText::~DynamicText()
{
}
