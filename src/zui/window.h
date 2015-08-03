#ifndef H_UIWINDOW
#define H_UIWINDOW

#include <SFML/Graphics.hpp>

#include "uicomponent.h"
#include "../vec2f.h"

namespace zui
{
    class Window : public UIComponent
    {
    public:
        Window();
        ~Window();
    
        void create(sf::Vector2f pos, Vec2f size, sf::Color color);
    
        void drawSelf(sf::RenderWindow* window, Vec2f totalPos);
    
        void setPosition(sf::Vector2f pos);
    private:
        sf::Vector2f size;
        sf::Color color;
    
        sf::RectangleShape shape;
    };
};
#endif
