#ifndef H_DRAWABLE_COMPONENT
#define H_DRAWABLE_COMPONENT

#include "component.h"
#include "../entity.h"

#include <SFML/Graphics.hpp>

namespace zen 
{
    class DrawableComponent : public Component
    {
    public:
        virtual void draw(sf::RenderTarget* window);
    protected:
        DrawableComponent();
        ~DrawableComponent();
    };
} /* namespace zen */
#endif
