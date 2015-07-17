#ifndef H_WORLD
#define H_WORLD

#include <vector>
#include <stdint.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "entitygroup.h"

class World
{
public:
    World();
    ~World();

    //void addEntity(Entity* entity);
    void addEntityGroup(EntityGroup* group, float paralaxAmount);

    void draw(sf::RenderWindow* window, sf::Vector2f cameraPos);
private:
    struct Layer
    {
        EntityGroup* eGroup;
        float paralaxAmount;
    };

    //std::vector<Entity*> entities;
    std::vector<Layer> layers;
};
#endif
