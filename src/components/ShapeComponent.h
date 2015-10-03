#ifndef H_SHAPE_COMPONENT
#define H_SHAPE_COMPONENT

#include "Component.h"
#include "../vec2f.h"

namespace zen 
{
    class ShapeComponent : public Component
    {
    public:
        ShapeComponent();
        ShapeComponent(Vec2f shape);
        
        void setShape(Vec2f shape);

        Vec2f getWorldBounds();
    private:
        Vec2f shape;
    };
} /* namespace zen */
#endif
