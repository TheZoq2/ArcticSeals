#ifndef H_HUMANENTITY
#define H_HUMANENTITY

#include "physicsentity.h"

class HumanEntity : public PhysicsEntity
{
public:
    HumanEntity(Vec2f size);
    virtual HumanEntity* clone();

    virtual void update(float time);

protected:
    float movementAmount; //Percentage of the max speed that the entity should move at right now
private:
};
#endif
