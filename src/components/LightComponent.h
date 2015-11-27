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

        void receiveComponentMessage(Component* other, int message) override;
    
    private:
        Light light;
        int lightID;

        LightManager* lightManager;
    };
} /* zen */ 
#endif
