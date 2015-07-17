#include "world.h"

World::World()
{
}
World::~World()
{
}

void World::addEntityGroup(EntityGroup* group, float paralaxAmount)
{
    Layer layer; //The new layer to add;
    layer.eGroup = group;
    layer.paralaxAmount = paralaxAmount;

    layers.push_back(layer);
}

void World::draw(sf::RenderWindow* window, sf::Vector2f cameraPos)
{
    for(std::vector<Layer>::iterator it = layers.begin(); it != layers.end(); it++)
    {
        Layer layer = *it;

        layer.eGroup->draw(window, cameraPos * layer.paralaxAmount);
    }
}
