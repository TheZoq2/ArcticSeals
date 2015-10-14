#include "KeyboardSystem.h"

#include "../components/PhysicsComponent.h"

using namespace zen;

void KeyboardSystem::run(Entity* entity, float time) 
{
    PhysicsComponent* physComp = entity->getComponent<PhysicsComponent>();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        physComp->jump();
    }
}
