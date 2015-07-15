#ifndef H_STATIC_ENTITY
#define H_STATIC_ENTITY

#include <SFML/Graphics.hpp>
#include <iostream>

#include "entity.h"
#include "sprite.h"

class StaticEntity : public Entity
{
public:
    void create(sf::Texture* texture);

    void setPosition(sf::Vector2f pos);

    void draw(sf::RenderWindow* window, sf::Vector2f cameraPos);
private:
    sf::Sprite sprite;

    sf::Vector2f pos;
};
#endif
