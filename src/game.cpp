#include "game.h"

void Game::setup()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Test");
    done = false;
    //worldView = window->getDefaultView();
    worldView = sf::View(Vec2f(0,0), Vec2f(1280, 720));
    
    zen::EntityGroup* mainGroup = this->world.getMainGroup();

    zen::Platform* groundPlatform = new zen::Platform();
    groundPlatform->addPoint(Vec2f(0,0));
    groundPlatform->addPoint(Vec2f(300,100));
    groundPlatform->addPoint(Vec2f(700,100));
    groundPlatform->addPoint(Vec2f(-700,100));

    movingPlatform.addPoint(0,0);
    movingPlatform.addPoint(100,0);
    movingPlatform.addPoint(200,0);
    movingPlatform.addPoint(300,25);
    movingPlatform.setPosition(Vec2f(700, -50));
    movingPlatform.addPoint(0,0);

    zen::Platform* platform3 = new zen::Platform();
    platform3->addPoint(100,0);
    platform3->addPoint(200,0);
    platform3->addPoint(300,25);
    platform3->setPosition(Vec2f(-300, -100));

    mainGroup->addPlatform(groundPlatform);
    mainGroup->addPlatform(&movingPlatform);
    mainGroup->addPlatform(platform3);

    //player = new zen::Player(Vec2f(30,100));
    //player->setPosition(Vec2f(5, -100));
    //mainGroup->addEntity(player);

    sf::Texture* particleTexture = new sf::Texture();
    particleTexture->loadFromFile("../media/img/particleTest.png");

    zen::Pathfinder pathfinder(mainGroup);

    
    std::shared_ptr<sf::Texture> testTexture = std::shared_ptr<sf::Texture>(new sf::Texture());
    testTexture->loadFromFile("../media/img/particleTest.png");
    testEntity.addComponent<zen::DrawableComponent>(
            std::unique_ptr<zen::DrawableComponent>(new zen::SpriteComponent(testTexture))
        );
}

void Game::loop()
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
            uiView.reset(visibleArea);
            //view.setViewport(sf::FloatRect(0,0,1,1));
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

    //Redraw stuff
    window->clear(sf::Color::Black);
    
    window->setView(worldView);
    world.update(frameTime);
    world.draw(window, Vec2f(0, 0));

    //sf::View view = window->getView();

    testEntity.draw(window);

    window->setView(uiView);
    uiView.setCenter(uiView.getSize().x / 2, uiView.getSize().y / 2);
    mainUIWindow.draw(window, Vec2f(0, 0));

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

