#ifndef H_SHAPE_SETUP_SYSTEM
#define H_SHAPE_SETUP_SYSTEM

#include "System.h"

namespace zen
{
    class ShapeSetupSystem : public System
    {
    public:
        ShapeSetupSystem();
        ~ShapeSetupSystem();
    
        virtual void run(Entity* owner, float time) override;
    private:
        /* data */
    };
} /* zen */ 
#endif
