#ifndef H_TEXTBUTTON
#define H_TEXTBUTTON

#include "button.h"
#include "../vec2f.h"

#include <memory>
#include <SFML/Graphics.hpp>

namespace zui
{
class TextButton : public Button
{
public:
    struct ButtonColor
    {
        sf::Color defaultColor;
        sf::Color hoverColor;
        sf::Color pressColor;
    };
    TextButton(std::string name);
    TextButton(std::string name, Vec2f pos, Vec2f size, ButtonColor colors, std::string text);

    void drawSelf(sf::RenderWindow* window, Vec2f actualPos);

    void setPosition(Vec2f pos);
    Vec2f getSize();

    bool posIsOnButton(Vec2f checkPos, Vec2f parentPos);

    void handleMouseMove(MouseData mouseData, Vec2f parentPos);
    bool handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos);
private:
    void changeState(State state);

    sf::RectangleShape box;
    sf::Text textDisplay;

    ButtonColor colors;

    Vec2f size;

    std::string text;
    
    sf::Font font;
};
}
#endif
