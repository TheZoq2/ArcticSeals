#include "component.h"

using namespace zen;

void Component::setOwner(Entity* owner) 
{
    this->owner = owner;
}
