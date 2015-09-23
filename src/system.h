#ifndef H_SYSTEM
#define H_SYSTEM

#include "entity.h"

namespace zen
{
    //Forward declaring the Entity class
    class Entity;

    /*
     * Base class for systems which define the behaviour of 
     * an entity
     */
    class System
    {
    public:
        void update(Entity* entity, float time);
    private:
    };
}
#endif
