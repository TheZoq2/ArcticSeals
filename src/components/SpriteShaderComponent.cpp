#include "SpriteShaderComponent.h"
#include <algorithm>

using namespace zen;

const std::size_t SpriteShaderComponent::MAX_LIGHTS = 64;

SpriteShaderComponent::SpriteShaderComponent(std::shared_ptr<sf::Texture> texture)
    :
    SpriteComponent(texture)
{
    
}

void SpriteShaderComponent::draw(sf::RenderTarget* target) 
{
    for(auto it : extraTextures)
    {
        shader->setUniform(it.first, *it.second.get());
    }

    //If the component has a light manager the light data should be pushed to the shader
    if(lightManager != nullptr)
    {
        shader->setUniform("lightAmount", (int)std::min(lightManager->lightAmount(), MAX_LIGHTS));
        
        for(std::size_t i = 0; i < MAX_LIGHTS || i < lightManager->lightAmount(); ++i)
        {
            shader->setUniform("lightRanges", lightManager->getRanges().data());
            shader->setUniform("lightPositions", lightManager->getPositions().data());
            shader->setUniform("lightColors", lightManager->getColors().data());
        }
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

void SpriteShaderComponent::setLightManager(LightManager* lightManager)
{
    this->lightManager = lightManager;
}
