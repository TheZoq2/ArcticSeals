#ifndef H_SWORD
#define H_SWORD

#include <math.h>

#include "meleeweapon.h"

namespace zen
{
    class Sword : public MeleeWeapon
    {
    public:
        Sword(float length) ;

        void changeState(SwingState newState);
        float getSwingChangeAmount();
    protected:

    };
}
#endif
