#include "particleeffect.h"

void update(float frameTime)
{

}

void ParticleEffect::addKeyframe(Keyframe keyframe)
{
    keyframes.push_back(keyframe);

    totalTime += keyframe.time;
}


