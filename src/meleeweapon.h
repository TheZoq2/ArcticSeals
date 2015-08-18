#ifndef H_MELEEWEAPON
#define H_MELEEWEAPON

#include "vec2f.h"
#include "line.h"

class MeleeWeapon
{
public:
    enum SwingType
    {
        HEAVY,
        LIGHT,
    }

    MeleeWeapon(float length);

    void update(float frameTime);

    virtual void Swing(SwingType type);
    
    virtual Line* getLine();
protected:
    enum SwingState
    {
        READY,
        PREPARING,
        SWING,
        RETURNING,
    }

    void generateLine();
    virtual bool readyForNextState();
    virtual void changeState(SwingState newState) = 0;

    Vec2f pos;
    Vec2f offset;
    float length;
    float angle;

    Line currentLine;

    SwingState state;
    SwingType swingType;

    Vec2f targetOffset;
    float targetAngle;
};
#endif
