#ifndef H_ENTITY
#define H_ENTITY

#include <SFML/System.hpp>

class Entity
{
public:
    virtual void draw(sf::RenderWindow* window, sf::Vector2f cameraPos) = 0;
private:
};

#endif
