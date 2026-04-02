#include "heart.h"

Heart::Heart(sf::Vector2f position)
    : sprite(texture)
{
    if (!texture.loadFromFile(texturePath))
        printf("heart sprite opening error");
    heartRects[0] = { { 76,0 }, { 18,16 } };
    heartRects[1] = { { 57,0 }, { 18,16 } };
    heartRects[2] = { { 38,0 }, { 18,16 } };
    heartRects[3] = { { 19,0 }, { 17,16 } };
    heartRects[4] = { { 0,0 }, { 17,16 } };

    sprite.setTexture(texture);
    sprite.setTextureRect(heartRects[health]);

    sprite.setScale({ 2.5f, 2.5f });
    sf::FloatRect heartBounds = sprite.getLocalBounds();
    sprite.setOrigin({ heartBounds.size.x / 2, heartBounds.size.y / 2 });
    sprite.setPosition(position);
}

void Heart::takeDamage()
{
    health = health - 1 <= 0 ? 0 : --health;
    sprite.setTextureRect(heartRects[health]);
}

Heart::~Heart()
{
}
