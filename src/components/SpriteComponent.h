#ifndef H_SPRITE_COMPONENT
#define H_SPRITE_COMPONENT

#include <memory>

#include "DrawableComponent.h"

namespace zen
{
    class SpriteComponent : public DrawableComponent
    {
    public:
        SpriteComponent(std::shared_ptr<sf::Texture> texture);

        void draw(sf::RenderTarget* target) override;
    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
    };
}
#endif
