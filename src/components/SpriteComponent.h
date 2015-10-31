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

        void setOwner(Entity* owner) override;
        void draw(sf::RenderTarget* target) override;

        void receiveComponentMessage(Component* other, int message) override;

        Vec2f getSize() override;
        void setOffset(Vec2f offset);
    protected:
        virtual void setPosition(Vec2f pos);
        virtual void setScale(Vec2f scale);
        virtual void setRotation(float angle);

        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        Vec2f offset = Vec2f(0,0);
    private:
        void updateOffset();
    };
}
#endif
