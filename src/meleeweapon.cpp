#include "meleeweapon.h"

MeleeWeapon::MeleeWeapon(float length)
{
    this->length = length;

    this->pos = Vec2f(0,0);
    this->angle = 0;
}

Line* MeleeWeapon::getLine()
{
    return &currentLine;
}

////////////////////////////////////////////////////////////////////////////

void MeleeWeapon::generateLine()
{
    Vec2f endPos; 
    endPos.x = pos.x + cos(angle) * length;
    endPos.y = pos.y + sin(angle) * length;

    currentLine.create(pos, endPos);
}
