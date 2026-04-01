#include "heart.h"

Heart::Heart(sf::Vector2f position)
    : sprite(texture)
{
    if (!texture.loadFromFile(texturePath))
        printf("heart sprite opening error");
        
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({ 0,0 }, { 16,16 }));

    sprite.setScale({ 2.5f, 2.5f });
    sf::FloatRect heartBounds = sprite.getLocalBounds();
    sprite.setOrigin({ heartBounds.size.x / 2, heartBounds.size.y / 2 });
    sprite.setPosition(position);
}

Heart::~Heart()
{

}
