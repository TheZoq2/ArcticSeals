#ifndef H_PLAYER
#define H_PLAYER

#include "physicsentity.h"
class Player : public PhysicsEntity
{
public:
    Player(Vec2f size);

    void update(float time);
private:
};
#endif
