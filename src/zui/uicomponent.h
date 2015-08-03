#ifndef H_UICOMPONENT
#define H_UICOMPONENT

#include <vector>
#include <map>
#include <utility>
#include <string>
#include <stdint.h>

#include <SFML/Graphics.hpp>

#include "inputcomponent.h"
#include "../vec2f.h"
#include "../mouseeventhandler.h"

namespace zui
{
class UIValueListener
{
public:
    virtual void onUIChange(InputComponent* changedComponent) = 0;
};

//Basic UI component interface. Contains functions for handling UIInput events aswell
//as drawing all children.
class UIComponent : public MouseListener
{
public:

    virtual void draw(sf::RenderWindow* window, sf::Vector2f parentPos);
    virtual void drawSelf(sf::RenderWindow* window, Vec2f parentPos) = 0;

    virtual void setPosition(Vec2f pos);
    
    void addChildComponent(UIComponent* child);

    void addUIValueListener(UIValueListener* listener, std::string inputName);
    //Function called when a child component has been updated
    void onInputChange(InputComponent* component); 

    //Event listener for mouse movement.
    void onMouseMove(MouseData mouseData);
    void onMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed);
    virtual void handleMouseMove(MouseData mouseData, Vec2f parentPos);
    //Handle mouse button press and releases. Return true if the component should bock the press for
    //parent components
    virtual bool handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos);
protected:
    UIComponent();
    UIComponent(Vec2f pos);

    sf::Vector2f pos;
    
    //std::vector<UIComponent*> components;
    std::vector< std::unique_ptr< UIComponent > > children;

    UIComponent* parent;
    
    std::vector< std::pair<std::string, UIValueListener*> > valueListeners;
};
};
#endif
