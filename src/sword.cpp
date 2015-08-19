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
            targetAngle = -M_PI / 12;
            targetOffset = Vec2f(0,0);
            break;
        }
        case(PREPARING):
        {
            targetAngle = -2 * M_PI / 3;
            targetOffset = Vec2f(10,20);
            break;
        }
        case(SWING):
        {
            targetAngle = M_PI / 3;
            targetOffset = Vec2f(15,-5);
            break;
        }
        case(RETURNING):
        {
            targetAngle = -M_PI / 12;
            targetOffset = Vec2f(0,0);
            break;
        }
    }
}

float Sword::getSwingChangeAmount()
{
    return 5;
}
