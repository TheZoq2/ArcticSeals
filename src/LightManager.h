#ifndef H_LIGHT_MANAGER
#define H_LIGHT_MANAGER

#include <vector>
#include <queue>
#include <memory>

#include "Light.h"
#include "IDList.h"

namespace zen
{
    class LightManager
    {
    public:

    private:
        IDList<Light> lights;
    };
} /* zen */ 
#endif
