#include "PhysicsSystem.h"

#include "../components/TransformComponent.h"
#include "../components/PhysicsComponent.h"
#include "../components/ShapeComponent.h"

const float GRAVITY = 9.82 * 90; //TODO: Move to good place

using namespace zen;

void PhysicsSystem::run(Entity* entity, float time) 
{
    //Get the required components from the entity
    TransformComponent* transform = entity->getTransformComponent();
    PhysicsComponent* physComp = entity->getComponent<PhysicsComponent>();
    ShapeComponent* shapeComp = entity->getComponent<ShapeComponent>();
    
    //The final position after the physics check
    Vec2f newPos = transform->getPosition();
    Vec2f newVel = physComp->getVelocity();

    switch (physComp->getState()) {
        case PhysicsComponent::FallState::ON_PLATFORM:
        {
            //Make sure the platform that the entity should be standing on exists
            uint32_t platformID = physComp->getPlatform();
            if(owner->platformExists(platformID))
            {
                Platform* platform = owner->getPlatformByID(platformID);

                float platformLocalX = physComp->getPlatformX();

                //Calculate the new position
                platformLocalX += physComp->getVelocity().x * time;
                
                //Make sure the new position is on the platform
                if(platform->xIsOnPlatform(platformLocalX))
                {
                    newPos = platform->getGlobalPos(platformLocalX);
                }
                else
                {
                    physComp->setState(PhysicsComponent::FallState::FALLING);
                }
            }
            break;
        }
        case(PhysicsComponent::FallState::RISING):
        {
            //Update position and velocity
            newPos += physComp->getVelocity() * time;
            newVel.y += GRAVITY * time;
            
            if(newVel.y > 0)
            {
                physComp->setState(PhysicsComponent::FallState::FALLING);
            }
            
            break;
        }
        case(PhysicsComponent::FallState::FALLING):
        {

            break;
        }
        default:
            
    }

    //TODO: Recalculate position with shape
}
