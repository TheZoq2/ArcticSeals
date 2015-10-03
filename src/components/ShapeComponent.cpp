#include "ShapeComponent.h"

#include "../entity.h"

using namespace zen;

ShapeComponent::ShapeComponent(Vec2f shape)
{
    setShape(shape);
}

void ShapeComponent::setShape(Vec2f shape) 
{
    this->shape = shape;
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

