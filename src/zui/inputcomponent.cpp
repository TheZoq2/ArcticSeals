#include "inputcomponent.h"

using namespace zui;

InputComponent::InputComponent(std::string name)
{
    this->name = name;
}

std::string InputComponent::getName()
{
    return this->name;
}
