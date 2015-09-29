#ifndef H_ENTITY
#define H_ENTITY

#include <typeinfo>
#include <typeindex>
#include <map>
#include <vector>

#include <SFML/System.hpp>

#include "entitygroup.h"
#include "vec2f.h"

#include "components/Component.h"
#include "components/TransformComponent.h"

#include "exceptions/missingcomponentexception.h"

namespace zen
{
    class EntityGroup;
    class Component;
    
    class Entity
    {
    public:
        //TODO: Rule of three
        
        Entity();
        //virtual ~Entity();
        
        virtual void draw(sf::RenderTarget* window);
        virtual void update(float time){};
    
        virtual void setDepth(int depth);
        virtual void setGroup(EntityGroup* group);
    
        int getDepth();
    
        template<class T>
        void addComponent(std::unique_ptr<T> component)
        {
            //Ensure that the object passed is an instance of component
            static_assert(std::is_base_of<Component, T>::value, "Added component needs to be subclass of Component");
        
            components.insert(std::make_pair(std::type_index(typeid(T)), std::move(component)));
        }

        //Return all components of a given type provided an entity can own more
        //than one of the component
        template<class T>
        T* getComponent()
        {
            //Ensure that the object passed is an instance of component
            static_assert(std::is_base_of<Component, T>::value, "Component class need to be subclass of Component");

            if(components.find(typeid(T)) == components.end())
            {
                throw MissingComponentException(typeid(T));
            }

            return dynamic_cast<T*>(components[typeid(T)].get());
        }
    protected:
    
        //This is the group that the entity is part of. If it is part of a group.
        //This group gets notified of any changes to the depth of the entity.
        EntityGroup* group; 

    private:
        int depth;
    
        std::map<std::type_index, std::unique_ptr<Component>> components;
        
        //Unique PTR because components depend on entities and entities on components. One needs to
        //be a pointer.
        std::unique_ptr<TransformComponent> transform;
    };
}

#endif
