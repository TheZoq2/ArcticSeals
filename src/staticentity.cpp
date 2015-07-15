#include "staticentity.h"

void StaticEntity::create(sf::Texture* texture)
{
    this->sprite.setTexture(*texture);
}

void StaticEntity::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
}

void StaticEntity::draw(sf::RenderWindow* window, sf::Vector2f cameraPos)
{
    this->sprite.setPosition(cameraPos + pos);
    window->draw(sprite);
}
