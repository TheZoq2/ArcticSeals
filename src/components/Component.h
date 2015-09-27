#ifndef H_COMPONENT
#define H_COMPONENT

#include "../entity.h"

namespace zen
{
    class Entity;

    class Component
    {
    public:
        
        void setOwner(Entity* owner);
    private:
        Entity* owner;
    };
}

#endif
