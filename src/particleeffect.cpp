#include "particleeffect.h"

void ParticleEffect::update(float frameTime)
{
    
}

void ParticleEffect::addKeyframe(Keyframe keyframe)
{
    keyframes.push_back(keyframe);

    totalTime += keyframe.time;
}


