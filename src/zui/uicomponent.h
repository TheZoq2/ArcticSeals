#ifndef H_UICOMPONENT
#define H_UICOMPONENT

#include <vector>
#include <stdint.h>

#include <SFML/Graphics.hpp>

namespace zui
{
    class UIComponent
    {
    public:
        virtual void draw(sf::RenderWindow* window, sf::Vector2f parentPos);
        virtual void drawSelf(sf::RenderWindow* window, sf::Vector2f parentPos) = 0;
    
        virtual void setPosition(sf::Vector2f pos);
    protected:
        sf::Vector2f pos;
        
        std::vector<UIComponent*> components;
    };
};
#endif
