#ifndef H_PARTICLEEFFECT
#define H_PARTICLEEFFECT

#include "vec2f.h"
#include "entity.h"

class ParticleEffect : public Entity
{
public:
    struct Keyframe
    {
        float time; //Time after last keyframe
        Vec2f minSpeed;
        Vec2f maxSpeed;

        Vec2f acceleration;
        
        Vec2f size;
    };

    virtual ParticleEffect* clone();
    
    ParticleEffect(Keyframe startKeyframe, float frequency);
    //void create();

    virtual void draw(sf::RenderWindow* window);
    virtual void update(float frameTime);
    
    virtual void addKeyframe(Keyframe keyframe);

    virtual void setFrequency(float frequency);
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
    void addVertex();

    float totalTime;
    std::vector<Keyframe> keyframes;
    
    //Emitter parameters
    float totalLifetime;
    float frequency; //Particles created per second
    float secondsPerParticle; //The time in miliseconds between particle spawns

    float lastSpawned;

    std::vector<Particle> particles;
    std::vector<sf::Vertex> vertecies;

};
#endif
