#ifndef H_PLATFORM_COMPONENT
#define H_PLATFORM_COMPONENT

#include "../platform.h"
#include "../vec2f.h"
#include "Component.h"

/*
 *  Component for keepign track of a collision platform.
 *
 *  The component itself is the 'owner' of the platform object which means that 
 *  it needs to be destroyed at the end of the entities life.
 */

namespace zen
{
    class PlatformComponent : public Component
    {
    public:
        PlatformComponent() = default;
        PlatformComponent(Platform* platform); //TODO: Possibly make unique_ptr or something

        void setOwner(Entity* owner) override;

        void setPlatform(Platform* platform);
        void setGroupID(uint32_t groupID);
        void setOffset(Vec2f offset);

        Platform* getPlatform();
        uint32_t getGroupID();
        Vec2f getOffset();

        void receiveComponentMessage(Component* other, int message) override;
    private:
        Platform* platform = nullptr;
        uint32_t groupID = 0; //The id of the platform in the group

        Vec2f offset = Vec2f(0,0);
    };
} /* zen */ 
#endif
