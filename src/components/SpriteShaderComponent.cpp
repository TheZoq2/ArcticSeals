#include "SpriteShaderComponent.h"

using namespace zen;

SpriteShaderComponent::SpriteShaderComponent(std::shared_ptr<sf::Texture> texture)
    :
    SpriteComponent(texture)
{
    
}

void SpriteShaderComponent::draw(sf::RenderTarget* target) 
{
    for(auto it : extraTextures)
    {
        shader->setParameter(it.first, *it.second.get());
    }

    target->draw(SpriteComponent::sprite, shader.get());
}


void SpriteShaderComponent::setShader(std::shared_ptr<sf::Shader> shader) 
{
    this->shader = shader;
}

void SpriteShaderComponent::addTexture(std::pair<std::string, std::shared_ptr<sf::Texture>> texture) 
{
    extraTextures.push_back(texture);
}
