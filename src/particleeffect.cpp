#include "particleeffect.h"

ParticleEffect::ParticleEffect(ParticleEffect::Keyframe keyframe, float frequency)
{
    //keyframes.push_back(keyframe);
    addKeyframe(keyframe);
    setFrequency(frequency);

    minLifetime = 0;
    currentTime = 0;
    lastSpawned = 0;
    minTimeMod = 1;
    maxTimeMod = 1;
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
    Particle newParticle;
    newParticle.pos = Entity::pos;
    newParticle.speed.x = minStartSpeed.x + (maxStartSpeed.x - minStartSpeed.x) * ((rand() % 1000) / 1000.0f);
    newParticle.speed.y = minStartSpeed.y + (maxStartSpeed.y - minStartSpeed.y) * ((rand() % 1000) / 1000.0f);
    newParticle.size = keyframes[0].size.val();
    newParticle.acceleration = keyframes[0].acceleration.val();
    newParticle.lifetime = minLifetime + (maxLifetime - minLifetime) * ((rand() % 1000) / 1000.0f);
    
    particles.push_back(newParticle);

    particles.back().vertecies.push_back(sf::Vertex(Vec2f(0,0), sf::Vector2f(0,0)));
    particles.back().vertecies.push_back(sf::Vertex(Vec2f(keyframes[0].size.val().x,0), sf::Vector2f(texture->getSize().x,0)));
    particles.back().vertecies.push_back(sf::Vertex(keyframes[0].size.val(), (sf::Vector2f) texture->getSize()));
    particles.back().vertecies.push_back(sf::Vertex(Vec2f(0,keyframes[0].size.val().y), sf::Vector2f(0,texture->getSize().y)));
}
void ParticleEffect::setParticleKeyframe(Particle* particle, int keyframeIndex)
{
    Keyframe keyframe = keyframes[keyframeIndex];

    particle->keyframe = keyframeIndex;
    particle->timeInKeyframe = 0;

    if(keyframe.texCoordEnd.isChanged())
    {
        //Recalculating the texture coordinates
        particle->vertecies[0].texCoords = texture->getSize() * keyframe.texCoordStart.val();
        particle->vertecies[1].texCoords = texture->getSize() * Vec2f(keyframe.texCoordEnd.val().x, keyframe.texCoordStart.val().y);
        particle->vertecies[2].texCoords = texture->getSize() * keyframe.texCoordStart.val();
        particle->vertecies[3].texCoords = texture->getSize() * keyframe.texCoordStart.val();
    }
}

