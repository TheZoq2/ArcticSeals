#ifndef H_SWORD
#define H_SWORD

#include <math.h>

#include "meleeweapon.h"

class Sword : public MeleeWeapon
{
public:
    Sword(float length) ;

    void changeState(SwingState newState);
protected:

};
#endif