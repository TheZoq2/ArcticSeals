#include "entity.h"

#include "components/SpriteComponent.h"

using namespace zen;

zen::Entity::Entity()
{
    this->depth = 0; //Setting the default depth

    //Initialise the transform component
    this->transform = std::unique_ptr<TransformComponent>(new TransformComponent);
}

void Entity::draw(sf::RenderTarget* target)
{
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
