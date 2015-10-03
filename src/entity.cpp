#include "entity.h"

#include "components/SpriteComponent.h"

using namespace zen;

zen::Entity::Entity()
{
    this->depth = 0; //Setting the default depth

    //Initialise the transform component
    this->transform = std::unique_ptr<TransformComponent>(new TransformComponent);
    this->transform->setOwner(this);
}

void Entity::update(float time)
{
    for(auto it : systems)
    {
        it->run(this, time);
    }
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
TransformComponent* Entity::getTransformComponent()
{
    return this->transform.get();
}

void Entity::addSystem(System* system)
{
    this->systems.push_back(system);
}
