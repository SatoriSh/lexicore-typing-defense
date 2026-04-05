#include "circle.h"

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
        };

    radius = dynText.getTotalWidth() / 1.3;

    speed -= dynText.getTotalWidth() * 2;
    if (speed < minSpeed) speed = minSpeed;

    transparencyChangingSpeed -= dynText.getTotalWidth() * 2;
    if (transparencyChangingSpeed < minTransparencyChangingSpeed) transparencyChangingSpeed = minTransparencyChangingSpeed;

    circleShape.setRadius(radius);

    updateOrigin();


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
        radius += explosionSpeed * dt;

        transparency -= transparencyChangingSpeed * dt;
        if (transparency < 0.0f) transparency = 0.0f;

        sf::Color explosionColor = sf::Color(
            isHeartHitExplosion ? 255 : 0,
            isHeartHitExplosion ? 0 : 255,
            0,
            transparency
        );

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
