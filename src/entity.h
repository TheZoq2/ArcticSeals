#ifndef H_ENTITY
#define H_ENTITY

#include <typeinfo>
#include <typeindex>
#include <map>
#include <vector>

#include <SFML/System.hpp>

#include "exceptions/MissingComponentException.h"
#include "exceptions/MissingSystemException.h"

#include "entitygroup.h"
#include "vec2f.h"

#include "components/Component.h"
#include "components/TransformComponent.h"

namespace zen
{
    class EntityGroup;
    class Component;
    class System;
    
    class Entity
    {
    public:
        //TODO: Rule of three
        
        Entity();
        //virtual ~Entity();
        
        virtual void update(float time);
    
        virtual void setDepth(int depth);
        virtual void setGroup(EntityGroup* group);
    
        int getDepth();
        TransformComponent* getTransformComponent();

        void addSystem(System* system);
        void removeSystem(System* system);

        template<typename ComponentType>
        ComponentType* addComponentSubscriber(Component* subscriber);
    
        template<class T>
        void addComponent(std::unique_ptr<T> component);

        //Return all components of a given type provided an entity can own more
        //than one of the component
        template<class T>
        T* getComponent();

        //Relay messages from one component to other components that are subscribed to it
        template<typename T>
        void handleComponentMessage(T* component, int message);
    protected:
    
        //This is the group that the entity is part of. If it is part of a group.
        //This group gets notified of any changes to the depth of the entity.
        EntityGroup* group; 

    private:
        int depth;
    
        std::map<std::type_index, std::unique_ptr<Component>> components;
        
        //Component message subscriptions
        std::map<std::type_index, std::vector<Component*>> componentSubscribers;

        //Unique PTR because components depend on entities and entities on components. One needs to
        //be a pointer.
        std::unique_ptr<TransformComponent> transform;

        std::vector<System*> systems;
    };

    /////////////////////////////////////////////////////////////////////////////////
    //                      Template function declarations
    /////////////////////////////////////////////////////////////////////////////////
    template<typename SubscriberClass>
    SubscriberClass* Entity::addComponentSubscriber(Component* subscriber)
    {
        static_assert(std::is_base_of<Component, SubscriberClass>::value, "A component can only subscribe to messages from other components");

        //Add the component to the vector of components subscribing to this specific class
        componentSubscribers[std::type_index(typeid(SubscriberClass))].push_back(subscriber);

        //Return a component of the correct type if such a component exists
        SubscriberClass* result = nullptr;
        try
        {
            result = getComponent<SubscriberClass>();
        }
        catch (const MissingComponentException& e)
        {
        }

        return result;
    }

    template<class T>
    void Entity::addComponent(std::unique_ptr<T> component)
    {
        //Ensure that the object passed is an instance of component
        static_assert(std::is_base_of<Component, T>::value, "Added component needs to be subclass of Component");
        component->setOwner(this);
        components.insert(std::make_pair(std::type_index(typeid(T)), std::move(component)));
    }


    template<class T>
    T* Entity::getComponent()
    {
        //Ensure that the object passed is an instance of component
        static_assert(std::is_base_of<Component, T>::value, "Component class need to be subclass of Component");

        if(components.count(typeid(T)) == 0)
        {
            throw MissingComponentException(std::type_index(typeid(T)));
        }

        return dynamic_cast<T*>(components[typeid(T)].get());
    }


    template<typename T>
    void Entity::handleComponentMessage(T* component, int message)
    {
        static_assert(std::is_base_of<Component, T>::value, "Message sender need to be subclass of component");

        //If there are any subscribers to this component type
        if(componentSubscribers.find(std::type_index(typeid(T))) != componentSubscribers.end())
        {
            std::vector<Component*> subscribers = componentSubscribers[std::type_index(typeid(T))];

            //Send the message to the subscribers
            for(auto& it : subscribers)
            {
                it->receiveComponentMessage(component, message);
            }
        }
    }
}

#endif
