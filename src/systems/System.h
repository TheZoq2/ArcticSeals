#ifndef H_SYSTEM
#define H_SYSTEM

#include "../entity.h"

namespace zen
{
    class System
    {
    public:
        virtual void run(Entity* entity) = 0;
    private:
    };
}
#endif
