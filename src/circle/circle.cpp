#include "circle.h"
#include <SFML/Graphics/Color.hpp>
#include <cstdint>

Circle::Circle(sf::Vector2f position, const sf::Vector2f directionToHeart, std::string text)
    : dynText(text), directionToHeart(directionToHeart), position(position)
{
    circleShape.setFillColor(fillColor);
    circleShape.setPointCount(pointCount);
    circleShape.setOutlineColor(outlineColor);
    circleShape.setOutlineThickness(outlineThickness);

    circleShape.setPosition(position);

    dynText.onWordCompleted = [this]()
        {
            addScore(dynText.getLettersCount() * scoreMultiplier);
            explode();
            if (onExplodeSuccess) onExplodeSuccess();
        };

    radius = dynText.getTotalWidth() / 1.3;
    if (dynText.getLettersCount() == 1)
        radius *= 2;

    speed -= dynText.getTotalWidth() * 2;
    if (speed < minSpeed) speed = minSpeed;

    transparencyChangingSpeed -= dynText.getTotalWidth() * 2;
    if (transparencyChangingSpeed < minTransparencyChangingSpeed) transparencyChangingSpeed = minTransparencyChangingSpeed;

    circleShape.setRadius(radius);

    updateOrigin();
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
        radius += explosionSpeed * dt;

        transparency -= transparencyChangingSpeed * dt;
        if (transparency < 0.0f) transparency = 0.0f;

        sf::Color explosionColor = isHeartHitExplosion ?
            sf::Color{255, 70, 40, (uint8_t)transparency} : 
            sf::Color{50, 220, 180, (uint8_t)transparency};

        circleShape.setFillColor(explosionColor);
        circleShape.setOutlineColor(explosionColor);

        circleShape.setRadius(radius);
        updateOrigin();

        if (transparency == 0.0f)
            isDestroyed = true;
    }
}

void Circle::explode()
{
    if (explosionStarted)
        return;

    circleShape.setPointCount(pointCountAfterExplosion);

    explosionStarted = true;
    dynText.circleExplosionStarted = true;
}

void Circle::updateOrigin()
{
    sf::FloatRect circleRect = circleShape.getLocalBounds();
    circleShape.setOrigin({ circleRect.size.x / 2, circleRect.size.y / 2 });
}

bool Circle::isExplosionStarted() { return explosionStarted; };

Circle::~Circle()
{
}
