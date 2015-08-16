#include "humanentity.h"

HumanEntity::HumanEntity(Vec2f size)
    : PhysicsEntity(size)
{
    moveState = NORMAL;

    maxSpeed = 180;
    maxAirAcceleration = 1000;
    rollMilliseconds = 1000;
    rollMultiplyer = 1.5;
    rollBaseMultiplyer = 0.5;
}
HumanEntity* HumanEntity::clone()
{
    return new HumanEntity(*this);
}

void HumanEntity::update(float time)
{
    PhysicsEntity::update(time);

    switch(moveState)
    {
        case NORMAL:
        {
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
            break;
        }
        case ROLLING:
        {
            float rolledTime = (rollClock.getElapsedTime() - rollStart).asMilliseconds();
            
            float newMultiplyer = rollMultiplyer * (1 - (rolledTime / rollMilliseconds)) + rollBaseMultiplyer;

            velocity.x = newMultiplyer * maxSpeed * rollDirection;

            if(rolledTime > rollMilliseconds)
            {
                moveState = NORMAL;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void HumanEntity::roll(int direction)
{
    if(moveState == MoveState::NORMAL && groundState == GroundState::ON_GROUND)
    {
        rollStart = rollClock.getElapsedTime();

        velocity.x = maxSpeed * direction * rollMultiplyer;
        this->rollDirection = direction;

        this->moveState = ROLLING;
    }
}
