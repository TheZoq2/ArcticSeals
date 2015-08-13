#include "editor.h"

void Editor::setup()
{
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "editor");

    uiView = window->getDefaultView();

    levelEditor.setupUI();
    
    mouseHandler.setup(window);
    mouseHandler.addListener(levelEditor.getMainWindow());
    mouseHandler.addListener(&levelEditor);
}
void Editor::loop()
{
    float frameTime = (gameClock.getElapsedTime() - lastFrame).asSeconds();
    lastFrame = gameClock.getElapsedTime();

    //Handle window events
    sf::Event event;
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window->close();
        }

        if(event.type == sf::Event::Resized)
        {
            //window->setSize(sf::Vector2<unsigned int>(width, height));
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            uiView.reset(visibleArea);
            uiView.setViewport(sf::FloatRect(0,0,1,1));

            //view.setSize(event.size.width, event.size.height);
            //window->setView(view);
        }
        if(event.type == sf::Event::MouseMoved)
        {
            mouseHandler.handleMoveEvent(&event);
        }
        if(event.type == sf::Event::MouseButtonPressed)
        {
            mouseHandler.handleMousePressed(&event);
        }
        if(event.type == sf::Event::MouseButtonReleased)
        {
            mouseHandler.handleMouseReleased(&event);
        }
    }
    //Exit if the window has been closed
    if(window->isOpen() == false)
    {
        this->done = true;
        return;
    }

    //Redraw stuff
    window->clear(sf::Color::Black);
    
    levelEditor.draw(window);

    window->setView(uiView);
    levelEditor.drawUI(window);

    window->display();

}
void Editor::cleanup()
{
    delete window;
}

bool Editor::isDone()
{
    return done;
}
