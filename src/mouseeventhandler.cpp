#include "mouseeventhandler.h"

void MouseEventHandler::addListener(MouseListener* listener)
{
    this->listeners.push_back(listener);
}
void MouseEventHandler::handleMoveEvent(sf::Event* event)
{
    //Creating a struct to store the data in 
    MouseData data;
    
    data.position = sf::Mouse::getPosition();
    data.moved = sf::Vector2i(event->mouseMove.x, event->mouseMove.y);

    for(unsigned int i = 0; i < listeners.size(); i++)
    {
        listeners[i]->onMouseMove(data);
    }
}
