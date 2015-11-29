#ifndef H_SPRITE_SHADER_COMPONENT
#define H_SPRITE_SHADER_COMPONENT

#include "SpriteComponent.h"

namespace zen
{
    class SpriteShaderComponent : public SpriteComponent
    {
    public:
        SpriteShaderComponent(std::shared_ptr<sf::Texture> texture);
    
        void draw(sf::RenderTarget* target) override;

        void setShader(std::shared_ptr<sf::Shader> shader);

        void addTexture(std::pair<std::string, std::shared_ptr<sf::Texture>> texture);
    private:
        std::vector<std::pair<std::string, std::shared_ptr<sf::Texture>>> extraTextures;
        std::shared_ptr<sf::Shader> shader;


    };
} /* zen */ 
#endif
