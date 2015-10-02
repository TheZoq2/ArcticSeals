#ifndef H_SYSTEM
#define H_SYSTEM

#include "../entitygroup.h"

namespace zen
{
    class Entity;
    class EntityGroup;

    class System
    {
    public:
        System();

        virtual void run(Entity* entity) = 0;
    private:
        EntityGroup* owner;
    };
}
#endif
