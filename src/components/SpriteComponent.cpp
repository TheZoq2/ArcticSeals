#include "SpriteComponent.h"

using namespace zen;

SpriteComponent::SpriteComponent(std::shared_ptr<sf::Texture> texture)
{
    sprite.setTexture(*texture.get());
}

void SpriteComponent::draw(sf::RenderTarget* target)
{
    target->draw(sprite);
}
