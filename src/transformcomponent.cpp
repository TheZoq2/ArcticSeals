#include "transformcomponent.h"

using namespace zen;

TransformComponent::TransformComponent() :
    Component(),
    pos(0,0),
    scale(0,0),
    angle(0)
{

}

void TransformComponent::setPosition(float x, float y)
{
    setPosition(Vec2f(x, y));
}
void TransformComponent::setPosition(Vec2f pos)
{
    this->pos = pos;
}
void TransformComponent::setScale(float x, float y)
{
    setScale(Vec2f(x, y));
}
void TransformComponent::setScale(Vec2f scale)
{
    this->scale = scale;
}
void TransformComponent::setAngle(float angle)
{
    this->angle = angle;
}
