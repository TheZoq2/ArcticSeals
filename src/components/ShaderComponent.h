#ifndef H_SHADER_COMPONENT
#define H_SHADER_COMPONENT

#include "Component.h"

#include <memory>

namespace zen
{
    class ShaderComponent : public Component
    {
    public:
        ShaderComponent(std::shared_ptr<sf::Shader> shader);

        void setShader(std::shared_ptr<sf::Shader> shader);
        sf::Shader* getShader();
    private:
        std::shared_ptr<sf::Shader> shader;
    };
} /* zen */ 
#endif
