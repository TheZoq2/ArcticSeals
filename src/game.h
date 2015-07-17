#ifndef H_GAME
#define H_GAME

#include <SFML/Graphics.hpp>

#include "world.h"
#include "spriteentity.h"
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
    sf::Texture texture2;

    UIWindow mainUIWindow;
    MouseEventHandler mouseHandler;
};

#endif
