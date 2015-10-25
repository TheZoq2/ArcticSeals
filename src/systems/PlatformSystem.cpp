#include "PlatformSystem.h"

#include "../exceptions/MissingComponentException.h"
#include "../components/PlatformComponent.h"

using namespace zen;

void PlatformSystem::run(Entity* entity, float time) 
{
    try
    {
        std::vector<PlatformComponent*> platforms = entity->getComponents<PlatformComponent>();

        for(auto& it : platforms)
        {
            if(owner->getPlatformByID(it->getGroupID()) == nullptr)
            {
                int newId = owner->addPlatform(it->getPlatform());
                it->setGroupID(newId);
            }
        }
    }
    catch (MissingComponentException e)
    {

    }
}

