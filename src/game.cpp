#include "game.h"

void Game::setup()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Test");

    texture.loadFromFile("../media/img/rockblob.png");
    texture2.loadFromFile("../media/img/fir3.png");
    SpriteEntity* testEntity = new SpriteEntity();
    SpriteEntity* testEntity1 = new SpriteEntity();
    SpriteEntity* testEntity2 = new SpriteEntity();
    testEntity->create(&texture2);
    testEntity1->create(&texture);
    testEntity2->create(&texture);
    
    testEntity->setPosition(sf::Vector2f(0, 0));
    testEntity->setDepth(1);
    testEntity1->setPosition(sf::Vector2f(0, 0));
    testEntity2->setPosition(sf::Vector2f(200, 50));

    //TODO: MEmory leak
    EntityGroup* testGroup = new EntityGroup();
    EntityGroup* testGroup2 = new EntityGroup();

    testGroup->addEntity(testEntity);
    testGroup->addEntity(testEntity1);
    //testGroup2->addEntity(testEntity2);
    
    world.addEntityGroup(testGroup, 1);
    world.addEntityGroup(testGroup2, 0.5);

    //mainUIWindow.create(sf::Vector2f(0, 0), sf::Vector2f(150, 900), sf::Color(60,60,60));

    mouseHandler.setup(this->window);
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
            unsigned int width = 1600;
            unsigned int height = 900;
            
            window->setSize(sf::Vector2<unsigned int>(width, height));
            window->setPosition(sf::Vector2i(0,0));
        }
        if(event.type == sf::Event::MouseMoved)
        {
            mouseHandler.handleMoveEvent(&event);
        }
    }

    //Redraw stuff
    window->clear(sf::Color::Black);
    
    world.draw(window, sf::Vector2f(0, 0));

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

