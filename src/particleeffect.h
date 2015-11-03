#ifndef H_PARTICLEEFFECT
#define H_PARTICLEEFFECT

#include <memory>

#include "vec2f.h"
#include "keyframeval.h"
#include "components/TransformComponent.h"

namespace zen
{
    class ParticleEffect
    {
    public:
        ParticleEffect(float frequency);

        virtual ParticleEffect* clone();
        
        //TODO READD
        //ParticleEffect(float frequency);

        virtual void draw(sf::RenderWindow* window);
        virtual void update(float frameTime);

        virtual void setFrequency(float frequency);

        virtual void setStartSpeed(Vec2f minStartSpeed, Vec2f maxStartSpeed);
        virtual void setMinLifetime(float minLifetime);
        virtual void setTimeMods(float minTimeMod, float maxTimeMod);
        virtual void setTexture(std::shared_ptr<sf::Texture> texture);
    private:
        struct Particle
        {
            float timeAlive;
            int seed; //Random number used to add variation between particles

            Vec2f origin; //The starting point of this specific particle
            Vec2f offset;
            Vec2f size; 
            float angle;

            std::vector<sf::Vertex> vertecies;
        };

        ParticleEffect();

        void addParticle();

        /*
         *  Function that decides when a particle gets removed from the system. The return value
         *  is the probability of the particle getting removed at the current time
         *
         *  returning 0 means a particle with that lifetime will never get removed and 1 guarantees
         *  removal
         */
        std::function<float(float, int)> deathFunction;
        /*
         *  Function that decides the acceleration at the current lifetime of a particle
         */
        std::function<Vec2f(float, int)> offsetFunction;
        /*
         *  Decides the change in angle of the particle at the specified keyframe
         */
        std::function<float(float, int)> angleFunction;
        /*
         *  Decides the size of the particle over time
         */
        std::function<Vec2f(float, int)> sizeFunction;
        /*
         *  Decides the current keyframe of the particle at the specified time.
         *  Return an integer < the amount of keyframes indicating the index of 
         *  the specified keyframe
         */
        std::function<int(float, int)> keyframeFunction;
        
        //Emitter parameters
        float currentTime;
        float frequency; //Particles created per second
        float secondsPerParticle; //The time in miliseconds between particle spawns
        TransformComponent transform;

        float lastSpawned;

        std::vector<Particle> particles;

        //Vector containing all the vertecies for all the particles currently being 
        //drawn. This is cleared and rebuilt evey time the update function is run 
        std::vector<sf::Vertex> vertecies;

        std::shared_ptr<sf::Texture> texture;
    };
}
#endif
