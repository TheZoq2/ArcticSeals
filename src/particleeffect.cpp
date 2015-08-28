#include "particleeffect.h"

ParticleEffect::ParticleEffect(ParticleEffect::Keyframe keyframe, float frequency)
{
    //keyframes.push_back(keyframe);
    addKeyframe(keyframe);
    setFrequency(frequency);

    vertecies.push_back(sf::Vertex(Vec2f(0,0), sf::Vector2f(0,0)));
    vertecies.push_back(sf::Vertex(Vec2f(keyframes.front().size.x,0), sf::Vector2f(1,0)));
    vertecies.push_back(sf::Vertex(keyframes.front().size, sf::Vector2f(1,1)));
    vertecies.push_back(sf::Vertex(Vec2f(0,keyframes.front().size.y), sf::Vector2f(0,1)));

    minLifetime = 0;
}

ParticleEffect* ParticleEffect::clone()
{
    return new ParticleEffect(*this);
}

void ParticleEffect::update(float frameTime)
{
    currentTime += frameTime;
    //Calculating how many particles need to be spawned this frame
    float timeSinceLastSpawn = currentTime - lastSpawned;
    float fParticlesToSpawn = timeSinceLastSpawn / secondsPerParticle;
    int particlesToSpawn = floor(fParticlesToSpawn);
    lastSpawned = currentTime - (fParticlesToSpawn - particlesToSpawn) * secondsPerParticle;

    //Spawn those particles
    for(int i = 0; i < particlesToSpawn; ++i)
    {
        Particle newParticle;
        newParticle.pos = Entity::pos;
        newParticle.speed.x = minStartSpeed.x + (maxStartSpeed.x - minStartSpeed.x) * ((rand() % 1000) / 1000.0f);
        newParticle.speed.y = minStartSpeed.y + (maxStartSpeed.y - minStartSpeed.y) * ((rand() % 1000) / 1000.0f);
        newParticle.size = keyframes[0].size;
        newParticle.acceleration = keyframes[0].acceleration;
        newParticle.lifetime = minLifetime + (maxLifetime - minLifetime) * ((rand() % 1000) / 1000.0f);

        particles.push_back(newParticle);

        vertecies.push_back(sf::Vertex(Vec2f(0,0), sf::Vector2f(0,0)));
        vertecies.push_back(sf::Vertex(Vec2f(keyframes[0].size.x,0), sf::Vector2f(1,0)));
        vertecies.push_back(sf::Vertex(keyframes[0].size, sf::Vector2f(1,1)));
        vertecies.push_back(sf::Vertex(Vec2f(0,keyframes[0].size.y), sf::Vector2f(0,1)));
    }
    
    std::vector<sf::Vertex>::iterator vertIterator = vertecies.begin();
    for(auto& particle : particles)
    {
        //Increasing the time this particle has been alive
        particle.timeAlive += frameTime;

        //Calculating the new position
        particle.speed += particle.acceleration * frameTime;
        particle.pos += particle.speed * frameTime;

        //Recalculating the vertecies
        vertIterator->position = particle.pos;
        (vertIterator + 1)->position = particle.pos + Vec2f(particle.size.x, 0);
        (vertIterator + 2)->position = particle.pos + Vec2f(particle.size.x, particle.size.y);
        (vertIterator + 3)->position = particle.pos + Vec2f(0, particle.size.y);
        
        //Increase the current vertex
        vertIterator += 4;
    }

    for(std::vector<Particle>::iterator particle = particles.begin(); particle != particles.end(); particle++)
    {
        //Checking if the particle has expired
        if(particle->timeAlive > particle->lifetime)
        {
            particle = particles.erase(particle);
            vertIterator = vertecies.erase(vertIterator, (vertIterator + 3));
        }
        if(particle == particles.end())
        {
            break;
        }
    }
}
void ParticleEffect::draw(sf::RenderWindow* window)
{
    window->draw(vertecies.data(), vertecies.size(), sf::Quads);
}

void ParticleEffect::addKeyframe(Keyframe keyframe)
{
    keyframes.push_back(keyframe);

    maxLifetime += keyframe.time;
}

void ParticleEffect::setFrequency(float frequency)
{
    this->frequency = frequency;

    secondsPerParticle = 1 / frequency;
}
void ParticleEffect::setStartSpeed(Vec2f minStartSpeed, Vec2f maxStartSpeed)
{
    this->minStartSpeed = minStartSpeed;
    this->maxStartSpeed = maxStartSpeed;
}
void ParticleEffect::setMinLifetime(float minLifetime)
{
    //Make sure the lifetime of the particle makes sense
    if(minLifetime > maxLifetime)
    {
        std::cerr << "Min lifetime is less than the total time in the keyframes" << std::endl;
    }

    this->minLifetime = minLifetime;
}
