#include "SpriteComponent.h"

#include "TransformComponent.h"
#include "../entity.h"

using namespace zen;

SpriteComponent::SpriteComponent(std::shared_ptr<sf::Texture> texture)
{
    this->texture = texture;
    this->sprite.setTexture(*texture);
}

void SpriteComponent::setOwner(Entity* owner)
{
    //Run the base class owner setting stuff
    DrawableComponent::setOwner(owner);
    
    //Subscribe to any messages we need
    owner->addComponentSubscriber<TransformComponent>(this);
}
void SpriteComponent::draw(sf::RenderTarget* target)
{
    target->draw(sprite);
}

void SpriteComponent::receiveComponentMessage(Component* other, int message)
{
    //Try casting the pointer to transform component
    TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(other);
    if(transformComponent != nullptr)
    {
        switch(message)
        {
            case(TransformComponent::POSITION_CHANGED):
            {
                sprite.setPosition(transformComponent->getPosition());
                break;
            }
            case(TransformComponent::SCALE_CHANGED):
            {
                sprite.setScale(transformComponent->getScale());
                break;
            }
            case(TransformComponent::ANGLE_CHANGED):
            {
                sprite.setRotation(transformComponent->getAngle());
                break;
            }
        }
    }
}
