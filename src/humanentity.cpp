#include "humanentity.h"

zen::HumanEntity::HumanEntity(Vec2f size)
    : PhysicsEntity(size),
    sword(75)
{
    moveState = NORMAL;

    maxSpeed = 180;
    maxAirAcceleration = 1000;
    rollMilliseconds = 1000;
    rollMultiplyer = 1.5;
    rollBaseMultiplyer = 0.5;
    
    
    movementDirection = 1;
}
zen::HumanEntity* zen::HumanEntity::clone()
{
    return new HumanEntity(*this);
}

void zen::HumanEntity::update(float time)
{
    PhysicsEntity::update(time);

    switch(moveState)
    {
        case NORMAL:
        {
            if(groundState == GroundState::ON_GROUND)
            {
                velocity.x = (maxSpeed * 2 * movementAmount); 
            }
            else
            {
                float addedVel = (maxAirAcceleration*time * 2 * movementAmount) ;

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

    //Calculating the last movement direction
    if(sword.isSwingReady())
    {
        if(velocity.x > 0)
        {
            movementDirection = 1;
        }
        else if(velocity.x < 0)
        {
            movementDirection = -1;
        }
    }

    sword.setPosition(pos);
    sword.setDirection(movementDirection);
    sword.update(time);
}

void zen::HumanEntity::draw(sf::RenderWindow* window)
{
    PhysicsEntity::draw(window);
    
    Line* line = sword.getLine();

    line->draw(window);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void zen::HumanEntity::roll(int direction)
{
    if(moveState == MoveState::NORMAL && groundState == GroundState::ON_GROUND)
    {
        rollStart = rollClock.getElapsedTime();

        velocity.x = maxSpeed * direction * rollMultiplyer;
        this->rollDirection = direction;

        this->moveState = ROLLING;
    }
}
