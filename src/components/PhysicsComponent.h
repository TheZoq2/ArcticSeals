#ifndef H_PHSYICS_COMPONENT
#define H_PHSYICS_COMPONENT

#include "Component.h"
#include "../platform.h"

namespace zen
{
    class PhysicsComponent : public Component
    {
    public:
        enum FallState
        {
            RISING,
            FALLING,
            ON_PLATFORM
        };

        PhysicsComponent();

        void setVelocity(Vec2f velocity);
        void setVelocity(float x, float y);
        void setAcceleration(Vec2f acceleration);
        void setAcceleration(float x, float y);
        void setPlatform(uint32_t platform, float localX);
        void setPlatformX(float localX);
        void setState(FallState state);

        Vec2f getVelocity();
        Vec2f getAcceleration();
        uint32_t getPlatform();
        float getPlatformX();
        FallState getState();

        //TODO: Move out of physics
        void jump();
        void walk(int direction);
    private:
        Vec2f velocity;
        Vec2f acceleration;

        float platformLocalX;
        uint32_t currentPlatform = 0;

        FallState state = FALLING;
    };
}
#endif

