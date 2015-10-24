#include "PlatformComponent.h"
#include "TransformComponent.h"
#include "../entity.h"

using namespace zen;

PlatformComponent::PlatformComponent(Platform* platform)
    : Component()
{
    setPlatform(platform);
}

void PlatformComponent::setOwner(Entity* owner) 
{
    Component::setOwner(owner);

    owner->addComponentSubscriber<TransformComponent>(this);
}

void PlatformComponent::setPlatform(Platform* platform) 
{
    this->platform = platform;
}
void PlatformComponent::setGroupID(uint32_t groupID) 
{
    this->groupID = groupID;
}
void PlatformComponent::setOffset(Vec2f offset) 
{
    this->offset = offset;
}

uint32_t PlatformComponent::getGroupID() 
{
    return groupID;
}
Platform* PlatformComponent::getPlatform() 
{
    return platform;
}
Vec2f PlatformComponent::getOffset() 
{
    return offset;
}

void PlatformComponent::receiveComponentMessage(Component* other, int message) 
{
    TransformComponent* transform = dynamic_cast<TransformComponent*>(other);

    if(transform != nullptr)
    {
        if(message == Component::MessageTypes::ADDED || message == TransformComponent::POSITION_CHANGED)
        {
            //Update the position of the platform
            Vec2f newPos = offset + transform->getPosition();

            platform->setPosition(newPos);
        }
    }
}


