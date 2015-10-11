#ifndef H_PHYSICS_SYSTEM
#define H_PHYSICS_SYSTEM

#include "System.h"

namespace zen
{
    class PhysicsSystem : public System
    {
    public:

        void run(Entity* entity, float time) override;
    private:

    };
}
#endif
