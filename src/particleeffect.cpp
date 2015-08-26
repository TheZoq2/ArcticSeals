#include "particleeffect.h"

void ParticleEffect::update(float frameTime)
{
    totalTime += frameTime;
    //Calculating how many particles need to be spawned this frame
    float timeSinceLastSpawn = totalTime - lastSpawned;
    float fParticlesToSpawn = timeSinceLastSpawn / millisPerParticle;
    int particlesToSpawn = floor(fParticlesToSpawn);
    lastSpawned = totalTime - (fParticlesToSpawn - particlesToSpawn) * millisPerParticle;

    //Spawn those particles
    for(int i = 0; i < particlesToSpawn; ++i)
    {
        Particle newParticle;
        newParticle.pos = Entity::pos;
        newParticle.speed = keyframes[0].minSpeed; //TODO: Calculate speed propperly
        newParticle.size = keyframes[0].size;

        particles.push_back(newParticle);

        for(int n = 0; n < 4; n++)
        {
            vertecies.push_back(sf::Vertex());
        }
    }
    
    //Iterate over all the particles
    std::vector<sf::Vertex>::iterator vertIterator = vertecies.begin();
    for(auto particle : particles)
    {
        //Calculating the new position
        particle.pos += particle.speed * frameTime;

        //Recalculating the vertecies
        vertIterator->position = particle.pos;
        (vertIterator + 1)->position = particle.pos + Vec2f(particle.size.x, 0);
        (vertIterator + 2)->position = particle.pos + Vec2f(particle.size.x, particle.size.y);
        (vertIterator + 3)->position = particle.pos + Vec2f(0, particle.size.y);

        vertIterator += 4;
    }
}
void ParticleEffect::draw(sf::RenderWindow* window)
{
    window->draw(vertecies.data(), vertecies.size(), sf::Quads);
}

void ParticleEffect::addKeyframe(Keyframe keyframe)
{
    keyframes.push_back(keyframe);

    totalTime += keyframe.time;
}

void ParticleEffect::setFrequency(float frequency)
{
    this->frequency = frequency;
    
    float milliFrequency = frequency/1000;

    millisPerParticle = 1 / milliFrequency;
}
