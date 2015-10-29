#include "ShaderComponent.h"

using namespace zen;

ShaderComponent::ShaderComponent(std::shared_ptr<sf::Shader> shader)
{
    setShader(shader);
}

void ShaderComponent::setShader(std::shared_ptr<sf::Shader> shader) 
{
    this->shader = shader;
}

sf::Shader* ShaderComponent::getShader() 
{
    return shader.get();
}

