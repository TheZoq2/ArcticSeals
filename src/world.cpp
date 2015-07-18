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
    sf::View view = window->getView();
    
    view.setCenter(cameraPos);

    window->setView(view);

    for(std::vector<Layer>::iterator it = layers.begin(); it != layers.end(); it++)
    {
        Layer layer = *it;

        //Calculating the center for this layer
        //For now, paralax scrolling will only be done on the x-axis
        sf::Vector2f paralaxPos = cameraPos;
        paralaxPos.x = cameraPos.x * layer.paralaxAmount;
        
        view.setCenter(paralaxPos);
        window->setView(view);
        
        layer.eGroup->draw(window);
    }
}
