#ifndef H_UIWINDOW
#define H_UIWINDOW

#include <SFML/Graphics.hpp>

#include "uicomponent.h"

namespace zui
{
    class Window : public UIComponent
    {
    public:
        Window();
        ~Window();
    
        void create(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
    
        void drawSelf(sf::RenderWindow* window, sf::Vector2f totalPos);
    
        void setPosition(sf::Vector2f pos);
    private:
        sf::Vector2f size;
        sf::Color color;
    
        sf::RectangleShape shape;
    };
};
#endif
