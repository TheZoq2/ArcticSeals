#include "spriteentity.h"


void zen::SpriteEntity::create(std::shared_ptr<sf::Texture> texture)
{
    this->sprite.setTexture(*texture);
    this->texture = texture;
}

zen::SpriteEntity* zen::SpriteEntity::clone()
{
    return new SpriteEntity(*this);
}

void zen::SpriteEntity::setPosition(Vec2f pos)
{
    Entity::setPosition(pos);
    this->sprite.setPosition(pos);
}
void zen::SpriteEntity::setScale(Vec2f scale)
{
    sprite.setScale(scale);
}

void zen::SpriteEntity::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
}

void zen::SpriteEntity::setOrigin(Vec2f origin)
{
    this->origin = origin;

    Vec2f coordOrigin;
    coordOrigin.x = sprite.getTextureRect().width * origin.x;
    coordOrigin.y = sprite.getTextureRect().height * origin.y;

    this->sprite.setOrigin(coordOrigin);
}

bool zen::SpriteEntity::pointIsOnEntity(Vec2f point)
{
    sf::FloatRect spriteShape = sprite.getGlobalBounds();

    if(spriteShape.contains(point))
    {
        return true;
    }
    return false;
}
