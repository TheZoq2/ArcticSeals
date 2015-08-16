#include "humanentity.h"

HumanEntity::HumanEntity(Vec2f size)
    : PhysicsEntity(size)
{
}
HumanEntity* HumanEntity::clone()
{
    return new HumanEntity(*this);
}

void HumanEntity::update(float time)
{
    PhysicsEntity::update(time);

    const int maxSpeed = 180;
    const float maxAirAcceleration = 1000;

    if(groundState == GroundState::ON_GROUND)
    {
        velocity.x = (maxSpeed * 2 * movementAmount / 100.0f); 

        if(sf::Joystick::isButtonPressed(0, 0))
        {
            jump(600);
        }
    }
    else
    {
        float addedVel = (maxAirAcceleration*time * 2 * movementAmount / 100.0f) ;

        velocity.x += addedVel;

        if(velocity.x > maxSpeed)
        {
            velocity.x = maxSpeed;
        }
        else if(velocity.x < -maxSpeed)
        {
            velocity.x = -maxSpeed;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
