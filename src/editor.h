#ifndef H_EDITOR
#define H_EDITOR

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "zui/window.h"

class Editor
{
public:
    void setup();
    void loop();
    void cleanup();

    bool isDone();
private:
    bool done;

    sf::RenderWindow* window;

    sf::Clock gameClock;
    sf::Time frameTime;
    sf::Time lastFrame;

    zui::Window mainUIWindow;
};
#endif
