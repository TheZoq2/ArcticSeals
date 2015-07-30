#include "player.h"

Player::Player(Vec2f size)
    : PhysicsEntity(size)
{
}

void Player::update(float time)
{
    PhysicsEntity::update(time);

    const int maxSpeed = 60;

    if(groundState == GroundState::ON_GROUND)
    {
        velocity.x = (maxSpeed * 2 * sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.0f); 

        std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.0f << std::endl;

        if(sf::Joystick::isButtonPressed(0, 0))
        {
            jump(300);
        }
    }
}
