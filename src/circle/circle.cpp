#include "circle.h"

Circle::Circle(sf::Vector2f position, std::string text, sf::RenderWindow& window)
    : dynText(text, window), window(window), position(position)
{
    circle.setRadius(radius);
    circle.setFillColor(fillColor);
    circle.setOutlineColor(outlineColor);
    circle.setOutlineThickness(outlineThickness);

    sf::FloatRect circleRect = circle.getLocalBounds();
    circle.setOrigin({ circleRect.size.x / 2, circleRect.size.y / 2 });

    circle.setPosition(position);
}

void Circle::update()
{
    render();
    dynText.update(position);
}

void Circle::render()
{
    window.draw(circle);
}

Circle::~Circle()
{

}
