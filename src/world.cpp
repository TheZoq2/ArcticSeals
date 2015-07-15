#include "world.h"

World::World()
{
}
World::~World()
{
}

void World::addEntity(Entity* entity)
{
    this->entities.push_back(entity);
}

void World::draw(sf::RenderWindow* window, sf::Vector2f cameraPos)
{
    for(uint16_t i = 0; i < entities.size(); i++)
    {
        entities.at(i)->draw(window, cameraPos);
    }
}
