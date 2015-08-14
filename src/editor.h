#ifndef H_EDITOR
#define H_EDITOR

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "zui/window.h"
#include "leveleditor.h"
#include "mouseeventhandler.h"


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
    sf::View uiView;

    sf::Clock gameClock;
    sf::Time frameTime;
    sf::Time lastFrame;

    LevelEditor levelEditor;

    MouseEventHandler mouseHandler;
};
#endif
