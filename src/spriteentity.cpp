#include "spriteentity.h"

void SpriteEntity::create(sf::Texture* texture)
{
    this->sprite.setTexture(*texture);
}

void SpriteEntity::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
}

void SpriteEntity::draw(sf::RenderWindow* window, sf::Vector2f cameraPos)
{
    this->sprite.setPosition(cameraPos + pos);
    window->draw(sprite);
}
