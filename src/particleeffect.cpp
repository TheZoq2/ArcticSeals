#include "particleeffect.h"

using namespace zen;

ParticleEffect::ParticleEffect()
{
    //Set default functions
    //Kill the particle immedietly after one second
    deathFunction = [](float t, int seed)
    {
        return t > 1;
    };

    //Constant acceleration upwards
    accelerationFunction = [](float t, int seed)
    {
        return Vec2f(0,-1);
    };

    //No rotation
    angleChangeFunction = [](float t, int seed)
    {
        return 0;
    };
    
    //Constant keyframe
    keyframeFunction = [](float t, int seed)
    {
        return 1;
    };
}
ParticleEffect::ParticleEffect(float frequency)
    : ParticleEffect()
{
    //keyframes.push_back(keyframe);
    setFrequency(frequency);
}

//ParticleEffect* ParticleEffect::clone()
//{
//    return new ParticleEffect(*this);
//}

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
        addParticle();
    }
    
    //Clearing the last list of vertecies
    vertecies.clear();

    for(auto& particle : particles)
    {
        //Increasing the time this particle has been alive
        particle.timeAlive += frameTime;

        //Calculating the new position
        particle.speed += particle.acceleration * frameTime;
        particle.pos += particle.speed * frameTime;

        Vec2f sizeOffset = particle.size / 2.0f;

        //Recalculating the vertecies
        particle.vertecies[0].position = particle.pos - sizeOffset;
        particle.vertecies[1].position = particle.pos + Vec2f(particle.size.x, 0) - sizeOffset;
        particle.vertecies[2].position = particle.pos + Vec2f(particle.size.x, particle.size.y) - sizeOffset;
        particle.vertecies[3].position = particle.pos + Vec2f(0, particle.size.y) - sizeOffset;


        //Adding the current particles vertecies to the list of vertecies to be
        //drawn by the draw function
        for(auto it : particle.vertecies)
        {
            vertecies.push_back(it);
        }
    }


    for(std::vector<Particle>::iterator particle = particles.begin(); particle != particles.end(); particle++)
    {
        //Checking if the particle has expired
        if(particle->timeAlive > particle->lifetime)
        {
            particle = particles.erase(particle) - 1;
        }
    }
}
void ParticleEffect::draw(sf::RenderWindow* window)
{
    sf::RenderStates renderState;
    renderState.texture = texture.get();

    window->draw(vertecies.data(), vertecies.size(), sf::Quads, renderState);

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
void ParticleEffect::setTexture(std::shared_ptr<sf::Texture> texture)
{
    this->texture = texture;
}
void ParticleEffect::setTimeMods(float minTimeMod, float maxTimeMod)
{
    this->minTimeMod = minTimeMod;
    this->maxTimeMod = maxTimeMod;
}


////////////////////////////////////////////////////////////////////
//                  Private member methods
////////////////////////////////////////////////////////////////////

void ParticleEffect::addParticle()
{
    float seed = rand();
    Particle newParticle;
    newParticle.seed = seed;
    newParticle.origin = transform.getPosition();
    newParticle.offset = offsetFunction(0, seed);
    newParticle.angle = angleFunction(0, seed);
    newParticle.size = sizeFunction(0, seed);
    
    particles.push_back(newParticle);

    particles.back().vertecies.push_back(sf::Vertex(Vec2f(0,0), sf::Vector2f(0,0)));
    particles.back().vertecies.push_back(sf::Vertex(Vec2f(newParticle.size.x,0), sf::Vector2f(texture->getSize().x,0)));
    particles.back().vertecies.push_back(sf::Vertex(newParticle.size, (sf::Vector2f) texture->getSize()));
    particles.back().vertecies.push_back(sf::Vertex(Vec2f(0,newParticle.size.y), sf::Vector2f(0,texture->getSize().y)));
}
