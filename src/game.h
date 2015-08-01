#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "world.h"
#include "spriteentity.h"
#include "zui/window.h"
#include "mouseeventhandler.h"
#include "line.h"
#include "vec2f.h"
#include "physicsentity.h"
#include "player.h"

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

    EntityGroup* generateForestBackground();

    float cameraX;

    sf::Clock gameClock;
    sf::Time frameTime;
    sf::Time lastFrame;

    Platform movingPlatform;
    float movingPos;
    bool moveDir;
};

#endif
