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
            rising,
            falling,
            onPlatform
        };

        void setVelocity(Vec2f velocity);
        void setVelocity(float x, float y);
        void setAcceleration(Vec2f acceleration);
        void setAcceleration(float x, float y);
        void setPlatform(Platform* platform, float localX);
        void setState(FallState state);

        Vec2f getVelocity();
        Vec2f getAcceleration();
        Platform* getPlatform();
        float getPlatformX();
        FallState getState();
    private:
        Vec2f velocity;
        Vec2f acceleration;

        float platformLocalX;
        Platform* currentPlatform = nullptr;

        FallState state;
    };
}
#endif

