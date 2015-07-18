#include "game.h"

void Game::setup()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Test");

    for(int i = 0; i < 5; i++)
    {
        world.addEntityGroup(generateForestBackground(), i * 0.20);
    }

    //mainUIWindow.create(sf::Vector2f(0, 0), sf::Vector2f(150, 900), sf::Color(60,60,60));

    mouseHandler.setup(this->window);
}

void Game::loop()
{
    cameraX += 0.3;
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
            unsigned int width = 1920;
            unsigned int height = 1080;
            
            //window->setSize(sf::Vector2<unsigned int>(width, height));
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window->setView(sf::View(visibleArea));
        }
        if(event.type == sf::Event::MouseMoved)
        {
            mouseHandler.handleMoveEvent(&event);
        }
    }

    //Redraw stuff
    window->clear(sf::Color::Black);
    
    world.draw(window, sf::Vector2f(cameraX, -256));

    //mainUIWindow.draw(window, sf::Vector2f(0, 0));

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

EntityGroup* Game::generateForestBackground()
{
    EntityGroup* group = new EntityGroup();

    std::vector<std::string> images;
    images.push_back("../media/img/fir1.png");
    images.push_back("../media/img/fir2.png");
    //images.push_back("../media/img/fir3.png");

    std::vector<sf::Texture*> textures;

    for(unsigned int i = 0; i < images.size(); i++)
    {
        textures.push_back(new sf::Texture());
        textures.back()->loadFromFile(images.at(i));
    }
    
    const int size = 4000;
    const int objectDistance = 200;
    const float maxOffset = objectDistance / 4;
    const float minScale = 0.5;
    const float maxScale = 1.5;

    for(int i = 1; i < size / objectDistance; i++)
    {
        float posX = i * objectDistance + ((maxOffset * 2) * (rand() % 1000) / 1000.0) / 2;
        float posY = 100;

        float scale = minScale + (maxScale - minScale) * (rand() % 1000) / 1000.0;

        //Create a sprite entity 
        SpriteEntity* entity = new SpriteEntity();

        entity->create(textures.at(rand() % textures.size()));

        entity->setOrigin(sf::Vector2f(0.5, 1));
        entity->setPosition(sf::Vector2f(posX, posY));
        entity->setScale(sf::Vector2f(scale, scale));
        entity->setDepth(rand() % 5);

        group->addEntity(entity);
    }

    return group;
}
