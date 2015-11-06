#include "game.h"

#include "systems/DrawingSystem.h"
#include "systems/randomMover.h"
#include "systems/PhysicsSystem.h"
#include "systems/KeyboardSystem.h"
#include "systems/PlatformSystem.h"
#include "components/PhysicsComponent.h"
#include "components/ShapeComponent.h"
#include "components/PlatformComponent.h"
#include "components/SpriteShaderComponent.h"

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
    movingPlatform.setPosition(Vec2f(300, -50));
    movingPlatform.addPoint(0,0);

    zen::Platform* platform3 = new zen::Platform();
    platform3->addPoint(100,0);
    platform3->addPoint(200,0);
    platform3->addPoint(300,25);
    platform3->setPosition(Vec2f(0, 0));

    mainGroup->addPlatform(groundPlatform);
    mainGroup->addPlatform(&movingPlatform);
    mainGroup->addPlatform(platform3);

    mainGroup->addSystem(std::unique_ptr<DrawingSystem>(new  DrawingSystem(window)));
    mainGroup->addSystem(std::unique_ptr<RandomMover>(new  RandomMover()));
    mainGroup->addSystem(std::unique_ptr<PhysicsSystem>(new  PhysicsSystem()));
    mainGroup->addSystem(std::unique_ptr<KeyboardSystem>(new KeyboardSystem()));
    mainGroup->addSystem(std::unique_ptr<PlatformSystem>(new PlatformSystem()));

    //player = new zen::Player(Vec2f(30,100));
    //player->setPosition(Vec2f(5, -100));
    //mainGroup->addEntity(player);


    zen::Pathfinder pathfinder(mainGroup);

    Entity* testPlatformEntity = new Entity();
    std::shared_ptr<sf::Texture> platformTexture = std::shared_ptr<sf::Texture>(new sf::Texture);
    platformTexture->loadFromFile("../media/img/rockblob.png");
    testPlatformEntity->addComponent<zen::DrawableComponent>(
            std::unique_ptr<zen::DrawableComponent>(new zen::SpriteComponent(platformTexture))
        );
    Platform* testPlatform = new Platform();
    testPlatform->addPoint(0,0);
    testPlatform->addPoint(200,100);
    testPlatformEntity->addComponent<zen::PlatformComponent>(
                std::unique_ptr<zen::PlatformComponent>(new zen::PlatformComponent(testPlatform))
            );
    testPlatformEntity->getTransformComponent()->setPosition(0,-100);
    testPlatformEntity->addSystem(mainGroup->getSystem<zen::DrawingSystem>());
    testPlatformEntity->addSystem(mainGroup->getSystem<zen::PlatformSystem>());
    mainGroup->addEntity(testPlatformEntity);

    std::shared_ptr<sf::Texture> testTexture = std::shared_ptr<sf::Texture>(new sf::Texture());
    testTexture->loadFromFile("../media/img/FallBirch1.png");

    std::shared_ptr<sf::Texture> testNormal = std::shared_ptr<sf::Texture>(new sf::Texture());
    testNormal->loadFromFile("../media/img/FallBirch1_normal.png");

    testShader = std::shared_ptr<sf::Shader>(new sf::Shader());
    testShader->loadFromFile("../media/shaders/test.vert", "../media/shaders/test.frag");

    
    std::unique_ptr<SpriteShaderComponent> spriteShaderComponent(new SpriteShaderComponent(testTexture));

    spriteShaderComponent->setShader(testShader);
    spriteShaderComponent->addTexture(std::make_pair("normalTexture", testNormal));
    spriteShaderComponent->setOffset(Vec2f(0.5, 0.5));
    
    Entity* testEntity = new Entity();
    testEntity->addComponent(std::unique_ptr<ShapeComponent>(new zen::ShapeComponent()));
    testEntity->addComponent<zen::DrawableComponent>(
            std::unique_ptr<zen::DrawableComponent>(std::move(spriteShaderComponent))
        );
    testEntity->addComponent(std::unique_ptr<PhysicsComponent>(new zen::PhysicsComponent()));

    testEntity->addSystem(mainGroup->getSystem<DrawingSystem>());
    testEntity->addSystem(mainGroup->getSystem<PhysicsSystem>());
    testEntity->addSystem(mainGroup->getSystem<KeyboardSystem>());

    testEntity->getTransformComponent()->setScale(0.3, 0.3);
    testEntity->getTransformComponent()->setPosition(10, -300);

    mainGroup->addEntity(testEntity);

    std::shared_ptr<sf::Texture> particleTexture(new sf::Texture());
    particleTexture->loadFromFile("../media/img/fireParticle.png");

    float lifetime = 1;
    //Test particle effect
    particleEffect = std::unique_ptr<ParticleEffect>(new ParticleEffect(50));
    particleEffect->setTexture(particleTexture, Vec2f(128,128), 16);
    particleEffect->setDeathFunction(
                [lifetime](float t, int seed)
                {
                    return t > lifetime;
                }
            );
    particleEffect->setOffsetFunction(
            [lifetime](float t, int seed)
            {
                float offsetAmount = 10;
                Vec2f offset = Vec2f(cos(seed * 100), sin(seed * 1000)) * offsetAmount;
                float angle = -M_PI / 2;
                return offset + Vec2f(cos(angle) * 200, sin(angle) * 200) * (t / 2.0f);
            }
        );
    particleEffect->setSizeFunction(
            [lifetime](float t, int seed)
            {
                return Vec2f(80,80);
            }
        );
    particleEffect->setKeyframeFunction(
            [lifetime](float t, int seed)
            {
               return ceil(t / lifetime * 16);
            }
        );
    particleEffect->setColorFunction([lifetime](float t, int seed)
            {
                int rStart = 207;
                int rEnd = 231;
                int gStart = 107;
                int gEnd = 182;
                int bStart = 0;
                int bEnd  = 7;

                int r = rStart + (rEnd - rStart) * t / lifetime;
                int g = gStart + (gEnd - gStart) * t / lifetime;
                int b = bStart + (bEnd - bStart) * t / lifetime;

                return sf::Color(r, g, b, 255 * t / lifetime);
            }
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

    particleEffect->update(frameTime);
    particleEffect->draw(window);

    //sf::View view = window->getView();

    //testEntity.draw(window);

    world.getMainGroup()->update(frameTime);
    world.getMainGroup()->draw(window);

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

