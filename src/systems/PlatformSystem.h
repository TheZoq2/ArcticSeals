#ifndef H_PLATFORM_SYSTEM
#define H_PLATFORM_SYSTEM

#include "System.h"

namespace zen
{
    class PlatformSystem : public System
    {
    public:
        PlatformSystem () = default;
    
        void run(Entity* entity, float time) override;
    private:
    };
} /* zen */ 
#endif
