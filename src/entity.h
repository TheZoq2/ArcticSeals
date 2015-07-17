#ifndef H_ENTITY
#define H_ENTITY

#include <SFML/System.hpp>
#include "entitygroup.h"

class EntityGroup;

class Entity
{
public:
    Entity();
    
    virtual void draw(sf::RenderWindow* window, sf::Vector2f cameraPos) = 0;

    void setDepth(int depth);
    void setGroup(EntityGroup* group);

    int getDepth();
private:
    int depth;

    //This is the group that the entity is part of. If it is part of a group.
    //This group gets notified of any changes to the depth of the entity.
    EntityGroup* group; 
};

#endif
