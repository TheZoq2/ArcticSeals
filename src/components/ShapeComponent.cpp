#include "ShapeComponent.h"

#include "../entity.h"
#include "DrawableComponent.h"
#include "../exceptions/MissingComponentException.h"

using namespace zen;

ShapeComponent::ShapeComponent(Vec2f shape)
{
    setShape(shape);
}
void ShapeComponent::setOwner(Entity* owner) 
{
    Component::setOwner(owner);

    owner->addComponentSubscriber<DrawableComponent>(this);
}

void ShapeComponent::receiveComponentMessage(Component* other, int message) 
{
    //Check if this is a transform component
    DrawableComponent* drawable = dynamic_cast<DrawableComponent*>(other);

    if(drawable != nullptr)
    {
        if(message == DrawableComponent::Message::SHAPE_CHANGED || Component::MessageTypes::ADDED)
        {
            shape = drawable->getSize();
        }
    }
}

void ShapeComponent::setShape(Vec2f shape) 
{
    this->shape = shape;
}

Vec2f ShapeComponent::getShape()
{
    return shape;
}
Vec2f ShapeComponent::getWorldBounds()
{
    Vec2f bounds(0,0);
    if(owner != nullptr)
    {
        bounds += owner->getTransformComponent()->getPosition();
    }
    
    return bounds;
}

