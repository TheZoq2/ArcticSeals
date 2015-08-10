#include "leveleditor.h"

void LevelEditor::setupUI()
{
    mainWindow.create(Vec2f(0,0), Vec2f(300, 1080), sf::Color(255,255,255, 150));

    //Create all the mode buttons
    Vec2f modeSize = Vec2f(40, 40);
    zui::TextButton::ButtonColor buttonColor;
    buttonColor.defaultColor = sf::Color(0,0,255);
    buttonColor.hoverColor = sf::Color(200,200,255);
    buttonColor.pressColor = sf::Color(100,100,255);

    zui::TextButton* selButton = new zui::TextButton(SELECT_BUTTON_NAME,
            Vec2f(10,10),
            modeSize,
            buttonColor,
            "Sel");
    modeButtons.push_back(std::unique_ptr<zui::TextButton>(selButton));
    
    zui::TextButton* moveButton = new zui::TextButton(MOVE_BUTTON_NAME,
            Vec2f(60, 10),
            modeSize,
            buttonColor,
            "Mov");
    modeButtons.push_back(std::unique_ptr<zui::TextButton>(moveButton));
            
    zui::TextButton* scaleButton = new zui::TextButton(SCALE_BUTTON_NAME,
            Vec2f(110, 10),
            modeSize,
            buttonColor,
            "Scl");
    modeButtons.push_back(std::unique_ptr<zui::TextButton>(scaleButton));

    zui::TextButton* rotateButton = new zui::TextButton(ROTATE_BUTTON_NAME,
            Vec2f(60, 10),
            modeSize,
            buttonColor,
            "Rot");
    modeButtons.push_back(std::unique_ptr<zui::TextButton>(rotateButton));

    for(auto& it : modeButtons)
    {
        mainWindow.addChildComponent(it.get());
    }
    mainWindow.addUIValueListener(this, SELECT_BUTTON_NAME);
    mainWindow.addUIValueListener(this, ROTATE_BUTTON_NAME);
    mainWindow.addUIValueListener(this, MOVE_BUTTON_NAME);
    mainWindow.addUIValueListener(this, SCALE_BUTTON_NAME);
}

void LevelEditor::draw(sf::RenderWindow* window)
{
    mainWindow.draw(window, Vec2f(0,0));
}

void LevelEditor::onUIChange(zui::InputComponent* changedComponent)
{
    
}

zui::Window* LevelEditor::getMainWindow()
{
    return &this->mainWindow;
}
