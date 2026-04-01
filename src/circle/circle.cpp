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

    //                  glow effect
    // glow = circle;
    // glow.setRadius(radius * 3);
    // glow.setOutlineThickness(0);
    // glow.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, 50));
    // sf::FloatRect glowRect = glow.getLocalBounds();
    // glow.setOrigin({ glowRect.size.x / 2, glowRect.size.y / 2 });
    // glow.setPosition(position);
}

void Circle::update(float dt)
{
    //position.x -= 50.0f * dt;
    //position.y -= 50.0f * dt;

    circle.setPosition(position);
    render();

    dynText.update(position);
}

void Circle::render()
{
    //window.draw(glow);
    window.draw(circle);
}

Circle::~Circle()
{

}
