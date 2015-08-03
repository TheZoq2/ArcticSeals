#include "mouseeventhandler.h"

void MouseEventHandler::setup(sf::Window* window)
{
    this->window = window;
}

void MouseEventHandler::addListener(MouseListener* listener)
{
    this->listeners.push_back(listener);
}

void MouseEventHandler::handleMoveEvent(sf::Event* event)
{
    //Creating a struct to store the data in 
    MouseData data;
    
    data.position = sf::Mouse::getPosition(*window);
    data.moved = sf::Vector2i(event->mouseMove.x, event->mouseMove.y);

    for(unsigned int i = 0; i < listeners.size(); i++)
    {
        listeners[i]->onMouseMove(data);
    }
}
void MouseEventHandler::handleMousePressed(sf::Event* event)
{
    Vec2f position(event->mouseButton.x, event->mouseButton.y);
    for(auto& it : listeners)
    {
        it->onMouseButtonChange(event->mouseButton.button, position, true);
    }
}
void MouseEventHandler::handleMouseReleased(sf::Event* event)
{
    Vec2f position(event->mouseButton.x, event->mouseButton.y);
    for(auto& it : listeners)
    {
        it->onMouseButtonChange(event->mouseButton.button, position, false);
    }
}
