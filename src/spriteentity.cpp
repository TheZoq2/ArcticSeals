#include "spriteentity.h"

void SpriteEntity::create(sf::Texture* texture)
{
    this->sprite.setTexture(*texture);
}

void SpriteEntity::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
    this->sprite.setPosition(pos);
}
void SpriteEntity::setScale(sf::Vector2f scale)
{
    sprite.setScale(scale);
}

void SpriteEntity::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
}

void SpriteEntity::setOrigin(sf::Vector2f origin)
{
    this->origin = origin;

    sf::Vector2f coordOrigin;
    coordOrigin.x = sprite.getTextureRect().width * origin.x;
    coordOrigin.y = sprite.getTextureRect().height * origin.y;

    std::cout << coordOrigin.x << std::endl;

    this->sprite.setOrigin(coordOrigin);
}
