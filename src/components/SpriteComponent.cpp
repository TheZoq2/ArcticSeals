#include "SpriteComponent.h"

#include "TransformComponent.h"
#include "../entity.h"
#include "ShaderComponent.h"

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
    TransformComponent* transComp =  owner->addComponentSubscriber<TransformComponent>(this);

    //if a transform component was already part of the entity 
    if(transComp != nullptr)
    {
        setPosition(transComp->getPosition());
        setScale(transComp->getScale());
        setRotation(transComp->getAngle());
    }
}
void SpriteComponent::draw(sf::RenderTarget* target)
{
    //Get the to use for drawing if one exists
    bool hasShader = false;
    ShaderComponent* shaderComponent = nullptr;
    try
    {
        shaderComponent = owner->getComponent<ShaderComponent>();
        hasShader = true;
    }
    catch(MissingComponentException e)
    {
    }

    if(hasShader)
    {
        target->draw(sprite, shaderComponent->getShader());
    }
    else
    {
        target->draw(sprite);
    }
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
                setPosition(transformComponent->getPosition());
                break;
            }
            case(TransformComponent::SCALE_CHANGED):
            {
                setScale(transformComponent->getScale());
                break;
            }
            case(TransformComponent::ANGLE_CHANGED):
            {
                setRotation(transformComponent->getAngle());
                break;
            }
        }
    }
}

Vec2f SpriteComponent::getSize()
{
    Vec2f size;
    size.x = sprite.getScale().x * texture->getSize().x;
    size.y = sprite.getScale().y * texture->getSize().y;
    return size;
}

/////////////////////////////////////////////////////////////
//                  Private methods
/////////////////////////////////////////////////////////////
void SpriteComponent::setPosition(Vec2f pos)
{
    this->sprite.setPosition(pos);
}
void SpriteComponent::setScale(Vec2f scale)
{
    sprite.setScale(scale);
    
    if(owner != nullptr)
    {
        owner->handleComponentMessage(this, DrawableComponent::Message::SHAPE_CHANGED);
    }
}
void SpriteComponent::setRotation(float angle)
{
    sprite.setRotation(angle);
}
