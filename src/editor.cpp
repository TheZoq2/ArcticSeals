#include "editor.h"

void Editor::setup()
{
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "editor");

    mainUIWindow.create(Vec2f(0,0), Vec2f(300,1080), sf::Color(150,150,150));

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
            sf::View view(visibleArea);
            view.setViewport(sf::FloatRect(0,0,1,1));
            //view.setSize(event.size.width, event.size.height);
            window->setView(view);
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
    
    mainUIWindow.draw(window, Vec2f(0,0));

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
