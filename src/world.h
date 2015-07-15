#ifndef H_WORLD
#define H_WORLD

#include <vector>
#include <stdint.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "entity.h"

class World
{
public:
    World();
    ~World();

    void addEntity(Entity* entity);

    void draw(sf::RenderWindow* window, sf::Vector2f cameraPos);
private:
    std::vector<Entity*> entities;
};
#endif
