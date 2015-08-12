#include "spriteentity.h"

void SpriteEntity::create(std::shared_ptr<sf::Texture> texture)
{
    this->sprite.setTexture(*texture);
}

SpriteEntity* SpriteEntity::clone()
{
    SpriteEntity* newEntity = new SpriteEntity();
    newEntity->create(this->texture);
    newEntity->setScale(this->scale);
    newEntity->setOrigin(this->origin);
    newEntity->setPosition(this->pos);

    return newEntity;
}

void SpriteEntity::setPosition(Vec2f pos)
{
    Entity::setPosition(pos);
    this->sprite.setPosition(pos);
}
void SpriteEntity::setScale(Vec2f scale)
{
    sprite.setScale(scale);
}

void SpriteEntity::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
}

void SpriteEntity::setOrigin(Vec2f origin)
{
    this->origin = origin;

    Vec2f coordOrigin;
    coordOrigin.x = sprite.getTextureRect().width * origin.x;
    coordOrigin.y = sprite.getTextureRect().height * origin.y;

    this->sprite.setOrigin(coordOrigin);
}
