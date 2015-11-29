#include "LightComponent.h"
#include "../entity.h"
#include "TransformComponent.h"

using namespace zen;

LightComponent::LightComponent(LightManager* lightManager)
{
    this->lightManager = lightManager;
}

void LightComponent::setLight(Light light)
{
    lightManager->forgetLight(lightID);

    this->light = light;

    lightID = this->lightManager->addLight(&light);
}

void LightComponent::setOwner(Entity* owner)
{
    Component::setOwner(owner);

    owner->addComponentSubscriber<TransformComponent>(this);
}
void LightComponent::setPosition(Vec2f position)
{
    this->light.setPosition(position);
}

void LightComponent::receiveComponentMessage(Component* other, int message) 
{
    TransformComponent* transComponent = dynamic_cast<TransformComponent*>(other);

    if(transComponent != nullptr) 
    {
        if(message == TransformComponent::POSITION_CHANGED)
        {
            light.setPosition(transComponent->getPosition());
        }
    }
}
