#include "Light.h"

using namespace zen;

Light::Light(Vec2f position, sf::Color color, float range) 
{
    this->position = position;
    this->color = color;
    this->range = range;
}
