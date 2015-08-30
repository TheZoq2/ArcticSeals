#ifndef H_PARTICLEEFFECT
#define H_PARTICLEEFFECT

#include <memory>

#include "vec2f.h"
#include "entity.h"
#include "keyframeval.h"

class ParticleEffect : public Entity
{
public:
    struct Keyframe
    {
        Keyframe()
        {
        }

        KeyframeVal<float> time; //Time after last keyframe

        KeyframeVal<Vec2f> acceleration;

        KeyframeVal<Vec2f> size;

        //The start and end pixel coordinates in float values where
        //{0,0} is the top left and {1,1} is the bottom right of the texture
        KeyframeVal<Vec2f> texCoordStart;
        KeyframeVal<Vec2f> texCoordEnd;
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
    virtual void setTimeMods(float minTimeMod, float maxTimeMod);
    virtual void setTexture(std::shared_ptr<sf::Texture> texture);
private:
    struct Particle
    {
        float timeAlive;
        float lifetime;
        //Time alive multiplier which affects death time and keyframe changes but not
        //movement
        float timeMod; 

        Vec2f pos;
        Vec2f speed;

        Vec2f size;
        Vec2f acceleration;

        int keyframe;
        float timeInKeyframe;
    
        std::vector<sf::Vertex> vertecies;
    };
    void addParticle();
    //Sets the values of a keyframe which can't be interpolated between frames
    //(like texture coordinates) to the value of the specified keyframe.
    void setParticleKeyframe(Particle* particle, int keyframeIndex);

    std::vector<Keyframe> keyframes;
    
    //Emitter parameters
    float currentTime;
    float frequency; //Particles created per second
    float secondsPerParticle; //The time in miliseconds between particle spawns

    float lastSpawned;

    std::vector<Particle> particles;

    //Vector containing all the vertecies for all the particles currently being 
    //drawn. This is cleared and rebuilt evey time the update function is run 
    std::vector<sf::Vertex> vertecies;

    Vec2f minStartSpeed;
    Vec2f maxStartSpeed;
    float maxLifetime; //Set by the total lifetime of all keyframes
    float minLifetime;
    bool lifetimeSpecified;
    float minTimeMod;
    float maxTimeMod;

    std::shared_ptr<sf::Texture> texture;
};
#endif
