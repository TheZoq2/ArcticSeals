#ifndef H_COMPONENT
#define H_COMPONENT

#include "../vec2f.h"

namespace zen
{
    class Entity;

    class Component
    {
    public:
        
        virtual void setOwner(Entity* owner);
    private:
        Entity* owner;
    };
}

#endif
