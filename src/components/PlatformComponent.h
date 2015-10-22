#ifndef H_PLATFORM_COMPONENT
#define H_PLATFORM_COMPONENT

#include "../platform.h"

/*
 *  Component for keepign track of a collision platform.
 *
 *  The component itself is the 'owner' of the platform object which means that 
 *  it needs to be destroyed at the end of the entities life.
 */

namespace zen
{
    class PlatformComponent
    {
    public:
        void setPlatform(Platform* platform);
        void setGroupID(uint32_t groupID);

        Platform* getPlatform();
        uint32_t getGroupID();
    private:
        Platform* platform = nullptr;
        uint32_t groupID = 0; //The id of the platform in the group
    };
} /* zen */ 
#endif
