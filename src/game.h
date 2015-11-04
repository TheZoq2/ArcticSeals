#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>
#include <dirent.h>

#include <SFML/Graphics.hpp>

//#include "depend/dirent.h"

#include "world.h"
#include "zui/window.h"
#include "zui/textbutton.h"
#include "zui/imglist.h"
#include "mouseeventhandler.h"
#include "line.h"
#include "vec2f.h"
#include "particleeffect.h"
#include "pathfinder.h"
#include "particleeffect.h"

#include "components/SpriteComponent.h"

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

    zen::World world;

    sf::Texture texture;
    sf::Texture texture2;

    zui::Window mainUIWindow;
    MouseEventHandler mouseHandler;
    sf::View uiView;
    sf::View worldView;

    float cameraX;

    sf::Clock gameClock;
    sf::Time frameTime;
    sf::Time lastFrame;

    zen::Platform movingPlatform;
    float movingPos;
    bool moveDir;

    std::unique_ptr<ParticleEffect> particleEffect;

    std::shared_ptr<sf::Shader> testShader;
};

#endif
