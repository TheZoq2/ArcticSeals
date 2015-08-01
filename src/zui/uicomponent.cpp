#include "uicomponent.h"

void UIComponent::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
}

void UIComponent::draw(sf::RenderWindow* window, sf::Vector2f parentPos)
{
    sf::Vector2f totalPos = pos + parentPos;
    //Draw this component, then draw all parent components above that
    this->drawSelf(window, totalPos);

    for(uint16_t i = 0; i < components.size(); i++)
    {
        components.at(i)->draw(window, totalPos);
    }
}
