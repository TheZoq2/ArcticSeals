#include "transformComponent.h"

using namespace zen;

void TransformComponent::setPosition(Vec2f position)
{
    this->position = position;
}
void TransformComponent::setPosition(float x, float y)
{
    setPosition(Vec2f(x, y));
}

void TransformComponent::setScale(Vec2f scale)
{
    this->scale = scale;
}
void TransformComponent::setScale(float x, float y)
{
    setScale(Vec2f(x, y));
}
void TransformComponent::setAngle(float angle)
{
    this->angle = angle;
}

Vec2f TransformComponent::getPosition()
{
    return position;
}
Vec2f TransformComponent::getScale()
{
    return scale;
}
float TransformComponent::getAngle()
{
    return angle;
}
