#include "meleeweapon.h"

using namespace zen;

MeleeWeapon::MeleeWeapon(float length)
{
    this->length = length;

    this->pos = Vec2f(0,0);
    this->angle = 0;

    this->state = SwingState::READY;
}

void MeleeWeapon::update(float frameTime)
{
    float angleDiff = targetAngle - angle;
    Vec2f offsetDiff = targetOffset - offset;

    offset += offsetDiff * frameTime * getSwingChangeAmount();
    angle += angleDiff * frameTime * getSwingChangeAmount();

    if(readyForNextState())
    {
        SwingState newState;
        switch(state)
        {
            case(PREPARING):
            {
                newState = SWING;
                break;
            }
            case(SWING):
            {
                newState = RETURNING;
                break;
            }
            case(RETURNING):
            {
                newState = READY;
                break;
            }
            default:
            {
                newState = state; //No change
            }
        }

        if(newState != state)
        {
            changeState(newState);
            state = newState;
        }
    }

    generateLine();
}

void MeleeWeapon::swing(MeleeWeapon::SwingType swingType)
{
    if(state == READY)
    {
        changeState(SwingState::PREPARING);
        this->state = SwingState::PREPARING;

        this->swingType = swingType;
    }
}

Line* MeleeWeapon::getLine()
{
    return &currentLine;
}
bool MeleeWeapon::isSwingReady()
{
    return state == SwingState::READY;
}

void MeleeWeapon::setPosition(Vec2f pos)
{
    this->pos = pos;
}
void MeleeWeapon::setDirection(int direction)
{
    this->direction = direction;
}

////////////////////////////////////////////////////////////////////////////

void MeleeWeapon::generateLine()
{
    Vec2f endPos; 
    endPos.x = pos.x + (offset.x + cos(angle) * length) * direction;
    endPos.y = pos.y + (offset.y + sin(angle) * length);

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
