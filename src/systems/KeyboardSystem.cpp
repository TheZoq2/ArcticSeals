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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        physComp->walk(1);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) )
    {
        physComp->walk(-1);
    }
    else
    {
        physComp->walk(0);
    }
}
