#ifndef H_SYSTEM
#define H_SYSTEM

#include "../entitygroup.h"

namespace zen
{
    class Entity;

    class System
    {
    public:
        virtual void run(Entity* entity) = 0;
    private:
    };
}
#endif
