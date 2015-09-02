#ifndef H_PATHFINDER
#define H_PATHFINDER

#include "entitygroup.h"

class Pathfinder
{
public:
    Pathfinder(EntityGroup* group);
private:
    void generatePaths();

    EntityGroup* entityGroup;

};
#endif
