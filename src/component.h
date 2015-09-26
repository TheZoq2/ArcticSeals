#ifndef H_COMPONENT
#define H_COMPONENT

#include "entity.h"

namespace zen
{
    class Entity;
    /*
     *
     * A component stores a specific kind of data for an entity
     *
     */
    class Component
    {
    public:
        //Set to true if an entity should be restricted to only one instance of
        //this component
        static bool IS_UNIQUE;

        Component();

        void setOwner(Entity* owner);

    private:
        Entity* owner;
    };
}
#endif
