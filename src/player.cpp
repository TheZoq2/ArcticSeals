#include "player.h"

Player::Player(Vec2f size)
    : HumanEntity(size)
{
}
Player* Player::clone()
{
    return new Player(*this);
}

void Player::update(float time)
{
    HumanEntity::update(time);

    HumanEntity::movementAmount = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

    /*const int maxSpeed = 180;
    const float maxAirAcceleration = 1000;

    if(groundState == GroundState::ON_GROUND)
    {
        velocity.x = (maxSpeed * 2 * sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.0f); 

        if(sf::Joystick::isButtonPressed(0, 0))
        {
            jump(600);
        }
    }
    else
    {
        float addedVel = (maxAirAcceleration*time * 2 * sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.0f) ;

        velocity.x += addedVel;

        if(velocity.x > maxSpeed)
        {
            velocity.x = maxSpeed;
        }
        else if(velocity.x < -maxSpeed)
        {
            velocity.x = -maxSpeed;
        }
    }*/
}
