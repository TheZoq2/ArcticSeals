#ifndef H_STATIC_ENTITY
#define H_STATIC_ENTITY

#include <SFML/Graphics.hpp>
#include <iostream>

#include "entity.h"
#include "sprite.h"
#include "vec2f.h"

class SpriteEntity : public Entity
{
public:
    void create(sf::Texture* texture);

    void setPosition(Vec2f pos);
    void setScale(Vec2f scale);

    void draw(sf::RenderWindow* window);

    //Sets the origin of the sprite in percentage.
    void setOrigin(Vec2f origin);
private:
    sf::Sprite sprite;

    Vec2f scale;
    Vec2f origin;
};

#endif
