#ifndef H_GAME
#define H_GAME

#include <SFML/Graphics.hpp>

#include "world.h"
#include "staticentity.h"
#include "uiwindow.h"
#include "mouseeventhandler.h"

class Game
{
public:
    void setup();
    void loop();
    void cleanup();
    
    bool isDone();

private:
    bool done;

    sf::RenderWindow* window;

    World world;

    sf::Texture texture;

    UIWindow mainUIWindow;
    MouseEventHandler mouseHandler;

    class MouseEventTest : public MouseListener
    {
        public:
            void onMouseMove(MouseData data)
            {
                std::cout << "x: " << data.position.x << std::endl;
            }
    };
    MouseEventTest mouseTest;
};

#endif
