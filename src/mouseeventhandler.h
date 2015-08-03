#ifndef H_MOUSEEVENTHANDLER
#define H_MOUSEEVENTHANDLER

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "vec2f.h"

struct MouseData
{
    sf::Vector2i position;
    sf::Vector2i moved;
};

//Interface for classes that need to listen to mouse events
class MouseListener
{
public:
    virtual void onMouseMove(MouseData mouseData){};
    virtual void onMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed){};
};

class MouseEventHandler
{
public:
    void setup(sf::Window* window);
    void addListener(MouseListener* listener);

    void handleMoveEvent(sf::Event* event);
    void handleMousePressed(sf::Event* event);
    void handleMouseReleased(sf::Event* event);
private:
    std::vector<MouseListener*> listeners;

    sf::Window* window;
};
#endif
