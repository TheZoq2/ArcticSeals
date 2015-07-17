#ifndef H_ENTITYGROUP
#define H_ENTITYGROUP

#include <vector>

#include <SFML/Graphics.hpp>

#include "entity.h"

class Entity;

class EntityGroup
{
public:
    //TODO: Make sure entity is only added once
    void addEntity(Entity* entity);

    void draw(sf::RenderWindow* window, sf::Vector2f position);

    void onEntityDepthChange(Entity* entity);

private:
    //Insert an entity in the correct location in the entity vector based on depth
    void insertEntity(Entity* entity); 

    std::vector<Entity*> entities;
};
#endif
