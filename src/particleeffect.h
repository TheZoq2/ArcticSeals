#ifndef H_PARTICLEEFFECT
#define H_PARTICLEEFFECT

#include <memory>

#include "vec2f.h"
#include "entity.h"

class ParticleEffect : public Entity
{
public:
    struct Keyframe
    {
        Keyframe()
            : time(0),
            acceleration(0,0),
            size(1,1),
            texCoordStart(0,0),
            texCoordEnd(1,1)
        {
        }

        float time; //Time after last keyframe

        Vec2f acceleration;
        
        Vec2f size;

        //The start and end pixel coordinates in float values where
        //{0,0} is the top left and {1,1} is the bottom right of the texture
        Vec2f texCoordStart;
        Vec2f texCoordEnd;
    };

    virtual ParticleEffect* clone();
    
    ParticleEffect(Keyframe startKeyframe, float frequency);
    //void create();

    virtual void draw(sf::RenderWindow* window);
    virtual void update(float frameTime);
    
    virtual void addKeyframe(Keyframe keyframe);

    virtual void setFrequency(float frequency);

    virtual void setStartSpeed(Vec2f minStartSpeed, Vec2f maxStartSpeed);
    virtual void setMinLifetime(float minLifetime);
    virtual void setTexture(std::shared_ptr<sf::Texture> texture);
private:
    struct Particle
    {
        float timeAlive;
        float lifetime;

        Vec2f pos;
        Vec2f speed;

        Vec2f size;
        Vec2f acceleration;

        int keyframe;
        float timeInKeyframe;
    };
    void addVertecies();

    std::vector<Keyframe> keyframes;
    
    //Emitter parameters
    float currentTime;
    float frequency; //Particles created per second
    float secondsPerParticle; //The time in miliseconds between particle spawns

    float lastSpawned;

    std::vector<Particle> particles;
    std::vector<sf::Vertex> vertecies;

    Vec2f minStartSpeed;
    Vec2f maxStartSpeed;
    float maxLifetime; //Set by the total lifetime of all keyframes
    float minLifetime;
    bool lifetimeSpecified;

    std::shared_ptr<sf::Texture> texture;
};
#endif
