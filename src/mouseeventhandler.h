#ifndef H_MOUSEEVENTHANDLER
#define H_MOUSEEVENTHANDLER

#include <SFML/Graphics.hpp>

#include <vector>

struct MouseData
{
    sf::Vector2i position;
    sf::Vector2i moved;
};

//Interface for classes that need to listen to mouse events
class MouseListener
{
public:
    virtual void onMouseMove(MouseData mouseData) = 0;
};

class MouseEventHandler
{
public:
    void setup(sf::Window* window);
    void addListener(MouseListener* listener);

    void handleMoveEvent(sf::Event* event);
private:
    std::vector<MouseListener*> listeners;

    sf::Window* window;
};
#endif
