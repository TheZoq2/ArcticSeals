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
        LIGHT
    };

    MeleeWeapon(float length);

    void update(float frameTime);

    virtual void swing(SwingType type);
    
    virtual Line* getLine();
    
    virtual void setPosition(Vec2f pos);
    virtual void setDirection(int direction);

    virtual bool isSwingReady();
protected:
    enum SwingState
    {
        READY,
        PREPARING,
        SWING,
        RETURNING,
    };

    void generateLine();
    virtual bool readyForNextState();
    virtual void changeState(SwingState newState) = 0;
    virtual float getSwingChangeAmount() = 0;

    Vec2f pos;
    Vec2f offset;
    float length;
    float angle;
    int direction;

    Line currentLine;

    SwingState state;
    SwingType swingType;

    Vec2f targetOffset;
    float targetAngle;
};
#endif
