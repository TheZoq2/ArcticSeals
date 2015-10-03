#ifndef H_RANDOM_MOVER
#define H_RANDOM_MOVER

#include "System.h"
#include "../entity.h"

namespace zen
{
    class RandomMover : public System
    {
    public:
        virtual void run(Entity* entity, float time) override
        {
            TransformComponent* tComponent = entity->getTransformComponent();

            tComponent->setPosition(rand() % 300, rand() % 300);
        }
    private:
    };
}

#endif
