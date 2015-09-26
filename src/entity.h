#ifndef H_ENTITY
#define H_ENTITY

#include <typeinfo>
#include <map>
#include <vector>

#include <SFML/System.hpp>
#include "entitygroup.h"

#include "vec2f.h"
#include "component.h"

namespace zen
{
    class EntityGroup;
    class Component;
    
    class Entity
    {
    public:
        Entity();
        //virtual ~Entity();
    
        virtual Entity* clone() = 0;
        
        virtual void draw(sf::RenderWindow* window) = 0;
        virtual void update(float time){};
    
        virtual void setDepth(int depth);
        virtual void setGroup(EntityGroup* group);
    
        int getDepth();
    
        template<class T>
        void addComponent(std::unique_ptr<T> component)
        {
            //Ensure that the object passed is an instance of component
            static_assert(std::is_base_of<Component, T>::value, "Added component needs to be subclass of Component");
        
            components.insert(std::make_pair(typeid(T), component));
        }
    protected:
        Vec2f pos;
    
        //This is the group that the entity is part of. If it is part of a group.
        //This group gets notified of any changes to the depth of the entity.
        EntityGroup* group; 

    private:
        int depth;
    
        std::map<std::type_info, std::unique_ptr<Component> > components;
    };
}

#endif
