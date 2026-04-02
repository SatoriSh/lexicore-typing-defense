#include "circle.h"

Circle::Circle(sf::Vector2f position, sf::Vector2f directionToHeart, std::string text)
    : dynText(text), directionToHeart(directionToHeart), position(position)
{
    circleShape.setRadius(radius);
    circleShape.setFillColor(fillColor);
    circleShape.setOutlineColor(outlineColor);
    circleShape.setOutlineThickness(outlineThickness);

    updateOrigin();

    circleShape.setPosition(position);

    //                  glow effect
    // glow = circleShape;
    // glow.setRadius(radius * 3);
    // glow.setOutlineThickness(0);
    // glow.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, 50));
    // sf::FloatRect glowRect = glow.getLocalBounds();
    // glow.setOrigin({ glowRect.size.x / 2, glowRect.size.y / 2 });
    // glow.setPosition(position);

}

void Circle::update(float dt)
{
    if (isDestroyed)
        return;

    if (!explosionStarted)
    {
        position += directionToHeart * speed * dt;

        circleShape.setPosition(position);
        dynText.update(position);
    }
    else
    {
        currentExplosionRadius += explosionSpeed * dt;
        circleShape.setRadius(currentExplosionRadius);

        updateOrigin();

        if (currentExplosionRadius >= explosionMaxRadius)
            isDestroyed = true;
    }
}

void Circle::explode()
{
    if (explosionStarted)
        return;

    explosionStarted = true;
    dynText.circleExplosionStarted = true;

    circleShape.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, 100));
}

void Circle::updateOrigin()
{
    sf::FloatRect circleRect = circleShape.getLocalBounds();
    circleShape.setOrigin({ circleRect.size.x / 2, circleRect.size.y / 2 });
}

Circle::~Circle()
{

}
