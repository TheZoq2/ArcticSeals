#include "entitygroup.h"

void EntityGroup::addEntity(Entity* entity)
{
    this->insertEntity(entity);
}

void EntityGroup::insertEntity(Entity* entity)
{
    std::vector<Entity*>::iterator it;

    //Go through the entities and find where to put the new entity
    for(it = entities.begin(); it != entities.end(); it++)
    {
        Entity* cEntity = *it;
        
        //Check if the depth is correct
        if(cEntity->getDepth() > entity->getDepth())
        {
            entities.insert(it, entity);
            //We found the correct location which means we are done. Return to avoid weird issues.
            return;
        }
    }
    
    //The entity should be added in the back because it has the lowest depth yet
    entities.push_back(entity);
}

void EntityGroup::onEntityDepthChange(Entity* entity)
{
    //Remove the entity from the list
    std::vector<Entity*>::iterator it;

    for(it = entities.begin(); it != entities.end(); it++)
    {
        //If this is the element we are looking for
        if(*it == entity)
        {
            entities.erase(it);
            break; //Avoid going further. Iterator is broken now
        }
    }

    //Insert the entity in the new position
    insertEntity(entity);
}

void EntityGroup::draw(sf::RenderWindow* window)
{
    std::vector<Entity*>::iterator it;

    for(it = entities.begin(); it != entities.end(); it++)
    {
        Entity* entity = *it;

        entity->draw(window);
    }
}
