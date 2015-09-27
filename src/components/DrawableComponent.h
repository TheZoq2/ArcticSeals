#ifndef H_DRAWABLE_COMPONENT
#define H_DRAWABLE_COMPONENT

#include <SFML/Graphics.hpp>

#include "Component.h"

namespace zen
{
    class DrawableComponent : public Component
    {
    public:
        virtual void draw(sf::RenderTarget* target) = 0;
    private:
    };
}
#endif
