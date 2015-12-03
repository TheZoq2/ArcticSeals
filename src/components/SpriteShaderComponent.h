#ifndef H_SPRITE_SHADER_COMPONENT
#define H_SPRITE_SHADER_COMPONENT

#include "SpriteComponent.h"
#include "../LightManager.h"

namespace zen
{
    class SpriteShaderComponent : public SpriteComponent
    {
    public:
        SpriteShaderComponent(std::shared_ptr<sf::Texture> texture);
    
        void draw(sf::RenderTarget* target) override;

        void setShader(std::shared_ptr<sf::Shader> shader);

        void addTexture(std::pair<std::string, std::shared_ptr<sf::Texture>> texture);

        void setLightManager(LightManager* lightManager);
    private:
        static const std::size_t MAX_LIGHTS;

        std::vector<std::pair<std::string, std::shared_ptr<sf::Texture>>> extraTextures;
        std::shared_ptr<sf::Shader> shader;

        LightManager* lightManager = nullptr;
    };
} /* zen */ 
#endif
