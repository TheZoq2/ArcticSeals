#include "game.h"

void Game::setup()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Test");

    texture.loadFromFile("../media/img/rockblob.png");
    StaticEntity* testEntity = new StaticEntity();
    StaticEntity* testEntity1 = new StaticEntity();
    StaticEntity* testEntity2 = new StaticEntity();
    testEntity->create(&texture);
    testEntity1->create(&texture);
    testEntity2->create(&texture);
    
    testEntity1->setPosition(sf::Vector2f(50, 0));
    testEntity2->setPosition(sf::Vector2f(200, 50));

    world.addEntity(testEntity);
    world.addEntity(testEntity1);
    world.addEntity(testEntity2);

    mainUIWindow.create(sf::Vector2f(0, 0), sf::Vector2f(150, 900), sf::Color(60,60,60));
}

void Game::loop()
{

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
            //unsigned int width = event.size.width;
            //unsigned int height = event.size.height;
            unsigned int width = 1280;
            unsigned int height = 720;
            
            window->setSize(sf::Vector2<unsigned int>(width, height));
        }
    }

    //Redraw stuff
    window->clear(sf::Color::Black);
    
    world.draw(window, sf::Vector2f(-200, 0));

    mainUIWindow.draw(window, sf::Vector2f(0, 0));

    window->display();

    //Exit if the window has been closed
    if(window->isOpen() == false)
    {
        this->done = true;
        return;
    }
}
void Game::cleanup()
{
    delete window;
}

bool Game::isDone()
{
    return this->done;
}

