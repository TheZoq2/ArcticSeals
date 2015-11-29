#ifndef H_LIGHT_COMPONENT
#define H_LIGHT_COMPONENT

#include "Component.h"

#include "../LightManager.h"

namespace zen
{
    class LightComponent : public Component
    {
    public:
        LightComponent(LightManager* lightManager);

        void setLight(Light light);

        void setOwner(Entity* owner) override;
        void setPosition(Vec2f position);

        void receiveComponentMessage(Component* other, int message) override;
    
    private:
        Light light;
        int lightID;

        /*
         *  The light manager that this component will add its lights to.
         *  It will be fetched from the entity group when setOwner is run
         */
        LightManager* lightManager = nullptr;
    };
} /* zen */ 
#endif
