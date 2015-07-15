#ifndef H_GAME
#define H_GAME

#include <SFML/Graphics.hpp>

#include "world.h"
#include "staticentity.h"
#include "uiwindow.h"

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
};

#endif
