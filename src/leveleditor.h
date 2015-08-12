#ifndef H_LEVELEDITOR
#define H_LEVELEDITOR

#include <SFML/Graphics.hpp>
#include <dirent.h>

#include "zui/window.h"
#include "zui/textbutton.h"
#include "zui/imglist.h"
#include "zui/uicomponent.h"
#include "zui/inputcomponent.h"
#include "entity.h"
#include "spriteentity.h"

class LevelEditor : public MouseListener, zui::UIValueListener
{
public:
    LevelEditor();

    void setupUI();

    void draw(sf::RenderWindow* window);

    void onUIChange(zui::InputComponent* changedComponent);

    zui::Window* getMainWindow();

    void onMouseMove(MouseData moveData, sf::RenderWindow* window);
    void onMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, sf::RenderWindow* window);
private:
    const static std::string SELECT_BUTTON_NAME;
    const static std::string MOVE_BUTTON_NAME;
    const static std::string SCALE_BUTTON_NAME;
    const static std::string ROTATE_BUTTON_NAME;
    const static std::string ENTITYSEL_BUTTON_NAME;
    const static std::string ENTITYSEL_LIST_NAME;

    void generateEntityList();

    void createGhostEntity(Vec2f worldPos);

    enum EditingMode
    {
        SELECT,
        MOVE,
        SCALE,
        ROTATE,
        CREATE,
    };
    EditingMode editingMode;

    sf::View worldView;

    Entity* ghostEntity;
    std::string newEntityName;

    zui::Window mainWindow;

    std::vector< zui::TextButton* > modeButtons;
    zui::TextButton* entitySelButton;
    zui::ImgList* entityList;
};
#endif
