#ifndef H_PARTICLE_COMPONENT
#define H_PARTICLE_COMPONENT

#include "DrawableComponent.h"
#include "../particleeffect.h"
namespace zen
{
    class ParticleComponent : public DrawableComponent
    {
    public:
        ParticleComponent(std::unique_ptr<ParticleEffect> particle);

        void draw(sf::RenderTarget* target) override;
    private:
        std::unique_ptr<ParticleEffect> particle;
    };
} /* zen */ 
#endif
