#ifndef H_KEYBOARD_SYSTEM
#define H_KEYBOARD_SYSTEM

#include <SFML/System.hpp>

#include "System.h"

namespace zen
{
    class KeyboardSystem : public System
    {
    public:
        void run(Entity* entity, float time);
    private:
    };
} /* KeyboardSystem */ 
#endif
