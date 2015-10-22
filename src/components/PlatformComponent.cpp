#include "PlatformComponent.h"

using namespace zen;

void PlatformComponent::setPlatform(Platform* platform) 
{
    this->platform = platform;
}
void PlatformComponent::setGroupID(uint32_t groupID) 
{
    this->groupID = groupID;
}

uint32_t PlatformComponent::getGroupID() 
{
    return groupID;
}
Platform* PlatformComponent::getPlatform() 
{
    return platform;
}

