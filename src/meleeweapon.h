#ifndef H_MELEEWEAPON
#define H_MELEEWEAPON

#include "vec2f.h"
#include "line.h"

class MeleeWeapon
{
public:
    MeleeWeapon(float length);

    virtual void standardAttack() = 0;
    virtual void heavyAttack() = 0;
    
    virtual Line* getLine();
protected:
    void generateLine();

    Vec2f pos;
    float length;
    float angle;

    Line currentLine;
};
#endif
