#include "DrawingSystem.h"

using namespace zen;

DrawingSystem::DrawingSystem(sf::RenderTarget* target)
    : System()
{
    this->target = target;
}

void DrawingSystem::run(zen::Entity* entity)
{
    DrawableComponent* drawable = entity->getComponent<DrawableComponent>();

    drawable->draw(target);
}

