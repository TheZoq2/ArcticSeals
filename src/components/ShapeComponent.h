#ifndef H_SHAPE_COMPONENT
#define H_SHAPE_COMPONENT

#include "../seal/components/Component.h"
#include "../seal/vec2f.h"

namespace zen 
{
    class ShapeComponent : public Component
    {
    public:
        ShapeComponent() = default;
        ShapeComponent(Vec2f shape);
        
        void setShape(Vec2f shape);

        Vec2f getWorldBounds();
        Vec2f getShape();

        void receiveComponentMessage(Component* other, int message) override;
        
        void setOwner(Entity* owner) override;
    private:
        Vec2f shape;
    };
} /* namespace zen */
#endif
