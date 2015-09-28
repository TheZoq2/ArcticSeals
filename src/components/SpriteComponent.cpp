#include "SpriteComponent.h"

using namespace zen;

SpriteComponent::SpriteComponent(std::shared_ptr<sf::Texture> texture)
{
    this->texture = texture;
    this->sprite.setTexture(*texture);
}

void SpriteComponent::draw(sf::RenderTarget* target)
{
    target->draw(sprite);
}
