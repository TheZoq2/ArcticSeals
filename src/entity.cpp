#include "entity.h"

Entity::Entity()
{
    this->depth = 0; //Setting the default depth
}

void Entity::setDepth(int depth)
{
    this->depth = depth;

    //Notify the group of the change in depth
    if(group != NULL)
    {
        group->onEntityDepthChange(this);
    }
}

void Entity::setGroup(EntityGroup* group)
{
    this->group = group;
}

int Entity::getDepth()
{
    return this->depth;
}
