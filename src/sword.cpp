#include "sword.h"

Sword::Sword(float length)
    : MeleeWeapon(length)
{
}

void Sword::changeState(SwingState newState)
{
    switch(newState)
    {
        case(READY):
        {
            targetAngle = 70;
            targetOffset = Vec2f(0,0);
            break;
        }
        case(PREPARING):
        {
            targetAngle = -10;
            targetOffset = Vec2f(10,20);
            break;
        }
        case(SWING):
        {
            targetAngle = 110;
            targetOffset = Vec2f(15,-5);
            break;
        }
        case(RETURNING):
        {
            targetAngle = 70;
            targetOffset = Vec2f(0,0);
            break;
        }
    }
}
