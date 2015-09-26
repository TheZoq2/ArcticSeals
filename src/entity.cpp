#include "entity.h"

using namespace zen;

/*
zen::Entity::Entity()
{
    this->depth = 0; //Setting the default depth
}
*/

void zen::Entity::setPosition(Vec2f pos)
{
    this->pos = pos;
}
void zen::Entity::setDepth(int depth)
{
    this->depth = depth;

    //Notify the group of the change in depth
    if(group != NULL)
    {
        group->onEntityDepthChange(this);
    }
}
void zen::Entity::setGroup(EntityGroup* group)
{
    this->group = group;
}

int zen::Entity::getDepth()
{
    return this->depth;
}
Vec2f zen::Entity::getPosition()
{
    return pos;
}

bool zen::Entity::pointIsOnEntity(Vec2f point)
{
    return false;
}
