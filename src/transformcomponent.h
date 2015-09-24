#ifndef H_TRANSFORM_COMPONENT
#define H_TRANSFORM_COMPONENT

#include "vec2f.h"
#include "component.h"

namespace zen
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent();
        
        void setPosition(float x, float y);
        void setPosition(Vec2f pos);
        void setScale(float x, float y);
        void setScale(Vec2f scale);
        void setAngle(float angle);

        Vec2f getPosition();
        Vec2f getScale();
        float getAngle();
    private:
        Vec2f pos;
        Vec2f scale;
        float angle;
    };
}
#endif
