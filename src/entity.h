#ifndef H_ENTITY
#define H_ENTITY

#include <SFML/System.hpp>
#include "entitygroup.h"

#include "vec2f.h"

class EntityGroup;

class Entity
{
public:
    Entity();

    virtual Entity* clone() = 0;
    
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void update(float time){};

    virtual void setPosition(Vec2f pos);
    void setDepth(int depth);
    void setGroup(EntityGroup* group);

    int getDepth();
protected:
    Vec2f pos;

    //This is the group that the entity is part of. If it is part of a group.
    //This group gets notified of any changes to the depth of the entity.
    EntityGroup* group; 
private:
    int depth;

};

#endif
