#ifndef H_EXTRA_TEXTURE_COMPONENT
#define H_EXTRA_TEXTURE_COMPONENT

#include "Component.h"

#include <string>
#include <memory>

namespace zen
{
    class ExtraTextureComponent : public Component
    {
    public:
        ExtraTextureComponent(std::string name, std::shared_ptr<sf::Texture> texture);
    
    private:
        
    };
} /* zen */ 
#endif
