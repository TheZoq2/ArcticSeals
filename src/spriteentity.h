#ifndef H_STATIC_ENTITY
#define H_STATIC_ENTITY

#include <SFML/Graphics.hpp>
#include <iostream>

#include "entity.h"
#include "sprite.h"

class SpriteEntity : public Entity
{
public:
    void create(sf::Texture* texture);

    void setPosition(sf::Vector2f pos);
    void setScale(sf::Vector2f scale);

    void draw(sf::RenderWindow* window);

    //Sets the origin of the sprite in percentage.
    void setOrigin(sf::Vector2f origin);
private:
    sf::Sprite sprite;

    sf::Vector2f pos;
    sf::Vector2f scale;
    sf::Vector2f origin;
};

#endif
