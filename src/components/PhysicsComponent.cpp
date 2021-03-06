#include "PhysicsComponent.h"

using namespace zen;

PhysicsComponent::PhysicsComponent():
    velocity(0,0),
    acceleration(0,0)
{
}
//Setters
void PhysicsComponent::setVelocity(float x, float y)
{
    setVelocity(Vec2f(x, y));
}
void PhysicsComponent::setVelocity(Vec2f velocity) 
{
    this->velocity = velocity;
}
void PhysicsComponent::setAcceleration(float x, float y)
{
    setAcceleration(Vec2f(x, y));
}
void PhysicsComponent::setAcceleration(Vec2f acceleration)
{
    this->acceleration = acceleration;
}
void PhysicsComponent::setPlatform(uint32_t platformID, float localX)
{
    this->currentPlatform = platformID;
    this->platformLocalX = localX;
}
void PhysicsComponent::setState(FallState state)
{
    this->state = state;
}
void PhysicsComponent::setPlatformX(float localX) 
{
    this->platformLocalX = localX;
}
float PhysicsComponent::getMaxSpeed()
{
    return maxSpeed;
}


//Getters
Vec2f PhysicsComponent::getVelocity()
{
    return velocity;
}
Vec2f PhysicsComponent::getAcceleration()
{
    return acceleration;
}
uint32_t PhysicsComponent::getPlatform()
{
    return currentPlatform;
}
float PhysicsComponent::getPlatformX()
{
    return platformLocalX;
}
PhysicsComponent::FallState PhysicsComponent::getState()
{
    return state;
}

//Movement functions TODO: Move out of physics component
void PhysicsComponent::jump() 
{
    if(state == FallState::ON_PLATFORM)
    {
        velocity.y -= 400;
        state = FallState::RISING;
    }
}
void PhysicsComponent::walk(int direction)
{
    if(state == FallState::ON_PLATFORM)
    {
        velocity.x = direction * maxSpeed;
    }
    else
    {
        acceleration.x = direction * 3;
    }
}
