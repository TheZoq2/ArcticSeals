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

        virtual void setOwner(Entity* owner) override;
        virtual void draw(sf::RenderTarget* target) override;

        virtual void receiveComponentMessage(Component* other, int message) override;
    protected:
        virtual inline void setPosition(Vec2f pos);
        virtual inline void setScale(Vec2f scale);
        virtual inline void setRotation(float angle);

        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
    };
}
#endif
