#ifndef H_LIGHT_MANAGER
#define H_LIGHT_MANAGER

#include <vector>
#include <queue>
#include <memory>

#include "Light.h"

namespace zen
{
    class LightManager
    {
    public:

    private:
        std::vector<std::shared_ptr<Light>> lights;

        //Queue of available spots in the light vector. When lights are added, IDs in this list are
        //used before appending to the end of the vector
        std::queue<int> freeSpots;
    };
} /* zen */ 
#endif
