#include "particleeffect.h"

ParticleEffect::ParticleEffect(ParticleEffect::Keyframe keyframe, float frequency)
{
    keyframes.push_back(keyframe);
    setFrequency(frequency);

}

ParticleEffect* ParticleEffect::clone()
{
    return new ParticleEffect(*this);
}

void ParticleEffect::update(float frameTime)
{
    totalTime += frameTime;
    //Calculating how many particles need to be spawned this frame
    float timeSinceLastSpawn = totalTime - lastSpawned;
    float fParticlesToSpawn = timeSinceLastSpawn / secondsPerParticle;
    int particlesToSpawn = floor(fParticlesToSpawn);
    lastSpawned = totalTime - (fParticlesToSpawn - particlesToSpawn) * secondsPerParticle;

    //Spawn those particles
    for(int i = 0; i < particlesToSpawn; ++i)
    {
        Particle newParticle;
        newParticle.pos = Entity::pos;
        newParticle.speed = keyframes[0].minSpeed + (keyframes[0].maxSpeed - keyframes[0].minSpeed) * ((rand() % 1000) / 1000.0f);
        newParticle.size = keyframes[0].size;
        newParticle.acceleration = keyframes[0].acceleration;

        particles.push_back(newParticle);

        vertecies.push_back(sf::Vertex(Vec2f(0,0), sf::Vector2f(0,0)));
        vertecies.push_back(sf::Vertex(Vec2f(keyframes[0].size.x,0), sf::Vector2f(1,0)));
        vertecies.push_back(sf::Vertex(keyframes[0].size, sf::Vector2f(1,1)));
        vertecies.push_back(sf::Vertex(Vec2f(0,keyframes[0].size.y), sf::Vector2f(0,1)));
    }
    
    //Iterate over all the particles
    std::vector<sf::Vertex>::iterator vertIterator = vertecies.begin();
    for(auto& particle : particles)
    {
        //Calculating the new position
        particle.speed += particle.acceleration * frameTime;
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

    secondsPerParticle = 1 / frequency;
}
