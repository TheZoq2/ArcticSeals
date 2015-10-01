#include "DrawingSystem.h"

using namespace zen;

DrawingSystem::DrawingSystem(EntityGroup* owner, sf::RenderTarget* target)
    : System(owner)
{
    this->target = target;
}

void DrawingSystem::run(zen::Entity* entity)
{
    DrawableComponent* drawable = entity->getComponent<DrawableComponent>();

    drawable->draw(target);
}

