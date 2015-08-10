#ifndef H_LEVELEDITOR
#define H_LEVELEDITOR

#include <SFML/Graphics.hpp>

#include "zui/window.h"
#include "zui/textbutton.h"
#include "zui/imglist.h"
#include "zui/uicomponent.h"
#include "zui/inputcomponent.h"

class LevelEditor : public zui::UIValueListener
{
public:
    void setupUI();

    void draw(sf::RenderWindow* window);

    void onUIChange(zui::InputComponent* changedComponent);

    zui::Window* getMainWindow();
private:
    enum EditingMode
    {
        SELECT,
        MOVE,
        SCALE,
        ROTATE,
    };

    zui::Window mainWindow;

    std::vector< std::unique_ptr< zui::TextButton > > modeButtons;

    const static std::string SELECT_BUTTON_NAME;
    const static std::string MOVE_BUTTON_NAME;
    const static std::string SCALE_BUTTON_NAME;
    const static std::string ROTATE_BUTTON_NAME;
};
#endif
