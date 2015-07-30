#include "entitygroup.h"

EntityGroup::EntityGroup()
{
    nextPlatformID = 0;
}
void EntityGroup::addEntity(Entity* entity)
{
    entity->setGroup(this);
    this->insertEntity(entity);
}
void EntityGroup::addPlatform(Platform* platform)
{

    IDPlatform newPlatform;
    newPlatform.id = nextPlatformID;
    newPlatform.platform = platform;

    this->platforms.push_back(newPlatform);

    nextPlatformID++;
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

void EntityGroup::update(float frameTime)
{
    for(auto it : entities)
    {
        it->update(frameTime);
    }
}
void EntityGroup::draw(sf::RenderWindow* window)
{
    std::vector<Entity*>::iterator it;

    for(it = entities.begin(); it != entities.end(); it++)
    {
        Entity* entity = *it;

        entity->draw(window);
    }

    for(auto it : platforms)
    {
        it.platform->draw(window);
    }
}

bool EntityGroup::platformExists(uint32_t id)
{
    for(auto it : platforms)
    {
        if(it.id == id)
        {
            return true;
        }
    }
    return false;
}
Platform* EntityGroup::getPlatformByID(uint32_t id)
{
    for(auto it : platforms)
    {
        if(it.id == id)
        {
            return it.platform;
        }
    }
    return NULL;
}

EntityGroup::PlatformCollisionResult EntityGroup::getPlatformCollision(Vec2f originPos, Line* line)
{

    //Finding which platform, if any is hit first
    PlatformCollisionResult result;
    result.intResult.intersected = false;
    float lowestDist;
    for(auto it : platforms)
    {
        Line::IntersectResult intResult = it.platform->getCollision(line);
        
        if(intResult.intersected == true)
        {
            float intersectDist = ((Vec2f)(intResult.pos - originPos)).length();
            //If this is the first intersection
            if(result.intResult.intersected == false)
            {
                result.intResult = intResult;
                result.platformID = it.id;
                
                lowestDist = intersectDist;
            }
            else
            {
                if(intersectDist < lowestDist)
                {
                    lowestDist = intersectDist;
                    result.intResult = intResult;
                    result.platformID = it.id;
                }
            }
        }
    }

    return result;
}
