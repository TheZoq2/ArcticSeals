#include "ParticleComponent.h"

using namespace zen;

ParticleComponent::ParticleComponent(std::unique_ptr<ParticleEffect> particle)
{
    this->particle = std::move(particle);
}
