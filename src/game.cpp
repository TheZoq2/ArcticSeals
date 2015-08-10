#include "game.h"

void Game::setup()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Test");
    done = false;

    for(int i = 0; i < 5; i++)
    {
        world.addEntityGroup(generateForestBackground(), i * 0.20);
    }
    Player* physEnt = new Player(sf::Vector2f(30, 100));
    physEnt->setPosition(Vec2f(500, -500));
    world.getMainGroup()->addEntity(physEnt);

    mainUIWindow.create(Vec2f(0, 0), Vec2f(150, 900), sf::Color(60,60,60));

    zui::TextButton::ButtonColor buttonColor;
    buttonColor.pressColor = sf::Color(150,150,255);
    buttonColor.hoverColor = sf::Color(100, 100, 255);
    buttonColor.defaultColor = sf::Color(0,0,255);
    zui::TextButton* testButton = new zui::TextButton("test", Vec2f(0,0), Vec2f(140, 60), buttonColor, "Click");
    testButton->setPosition(Vec2f(800,400));
    mainUIWindow.addChildComponent(testButton);
    mainUIWindow.addUIValueListener(&uiTest, "test");
    mainUIWindow.addUIValueListener(&uiTest, "testList");

    mouseHandler.setup(this->window);
    mouseHandler.addListener(&mainUIWindow);

    //Lots of memory leaks here
    Platform* platform = new Platform();
    platform->create(Vec2f(0,0));
    platform->addPoint(-200,0);
    platform->addPoint(100, 25);
    platform->addPoint(300, -5);

    Platform* platform2 = new Platform();
    platform2->create(Vec2f(0,100));
    platform2->addPoint(400, 0);
    platform2->addPoint(500, 0);
    platform2->addPoint(800, 100);

    movingPlatform.create(Vec2f(100, -100));
    movingPlatform.addPoint(0, 0);
    movingPlatform.addPoint(100, 0);
    movingPlatform.addPoint(200, 20);

    world.getMainGroup()->addPlatform(platform);
    world.getMainGroup()->addPlatform(platform2);
    world.getMainGroup()->addPlatform(&movingPlatform);

    //Searching for files in the img directory
    const std::string imgDir = "../media/img/";

    //Generate a vector of images
    std::vector<std::pair<std::string, std::string> > imgElements;

    DIR* dir;
    struct dirent* ent;
    if((dir = opendir(imgDir.data())) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            std::cout << "Found file: " << ent->d_name << " of type: " << ent->d_type << std::endl;
            
            std::string filename = ent->d_name;

            //If the file type is a .png
            if(filename.find_last_not_of(".png") != filename.length() -1 && filename.find(".png") != std::string::npos)
            {
                imgElements.push_back(std::pair<std::string, std::string>(imgDir + filename, imgDir + filename));
            }
        }
        closedir(dir);
    }

    zui::ImgList* testList = new zui::ImgList(imgElements, Vec2f(100,0), Vec2f(500, 500), "testList");
    mainUIWindow.addChildComponent(testList);
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
            view.setViewport(sf::FloatRect(0,0,1,1));
            //view.setSize(event.size.width, event.size.height);
            window->setView(view);

            std::cout << "Window size: " << window->sf::Window::getSize().x << "  "<< view.getSize().x << std::endl;
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
    


    //movingPlatform.setPosition(Vec2f(100, movingPos));

    world.update(frameTime);
    world.draw(window, Vec2f(cameraX, -256));

    sf::View view = window->getView();

    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    window->setView(view);
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

        entity->setOrigin(Vec2f(0.5, 1));
        entity->setPosition(Vec2f(posX, posY));
        entity->setScale(Vec2f(scale, scale));
        entity->setDepth(rand() % 5);

        group->addEntity(entity);
    }

    return group;
}
