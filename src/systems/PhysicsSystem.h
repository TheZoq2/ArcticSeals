#ifndef H_PHYSICS_SYSTEM
#define H_PHYSICS_SYSTEM

#include "System.h"
#include "../components/PhysicsComponent.h"

namespace zen
{
    class PhysicsSystem : public System
    {
    public:

        void run(Entity* entity, float time) override;
    private:

        Vec2f clampVelocity(Vec2f currentVel, PhysicsComponent* component);

    };
}
#endif
