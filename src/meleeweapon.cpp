#include "meleeweapon.h"

MeleeWeapon::MeleeWeapon(float length)
{
    this->length = length;

    this->pos = Vec2f(0,0);
    this->angle = 0;

    this->state = SwingState::READY;
}

Line* MeleeWeapon::getLine()
{
    return &currentLine;
}

////////////////////////////////////////////////////////////////////////////

void MeleeWeapon::generateLine()
{
    Vec2f endPos; 
    endPos.x = pos.x + offset.x + cos(angle) * length;
    endPos.y = pos.y + offset.y + sin(angle) * length;

    currentLine.create(pos + offset, endPos);
}

bool MeleeWeapon::readyForNextState()
{
    bool ready = true;

    ready = ready && std::abs(angle - targetAngle) < 0.1;

    ready = ready && std::abs(offset.x - targetOffset.x) < 1;
    ready = ready && std::abs(offset.y - targetOffset.y) < 1;

    return ready;
}
