#include "textbutton.h"

using namespace zui;


TextButton::TextButton(std::string name, Vec2f pos, Vec2f size, TextButton::ButtonColor colors, std::string text)
    : Button(pos, name)
{
    this->text = text;
    this->size = size;
    this->colors = colors;
    
    //Creating the shape
    box.setSize(size);
    textDisplay.setString(text);
}

void TextButton::drawSelf(sf::RenderWindow* window, Vec2f parentPos)
{
    box.setPosition(pos + parentPos);
    
    if(state == State::PRESSED)
    {
        box.setFillColor(colors.pressColor);
    }
    else if(state == State::HOVERED)
    {
        box.setFillColor(colors.hoverColor);
    }
    else
    {
        box.setFillColor(colors.defaultColor);
    }

    textDisplay.setPosition(pos + parentPos);

    window->draw(box);
    window->draw(textDisplay);
}

void TextButton::setPosition(Vec2f pos)
{
    UIComponent::setPosition(pos);
}

bool TextButton::posIsOnButton(Vec2f checkPos, Vec2f parentPos)
{
    Vec2f fullPos = pos + parentPos;

    if(checkPos.x > fullPos.x && checkPos.x < fullPos.x + size.x && checkPos.y > fullPos.y && checkPos.y < fullPos.y + size.y)
    {
        return true;
    }
    return false;
}

void TextButton::handleMouseMove(MouseData mouseData, Vec2f parentPos)
{
    UIComponent::handleMouseMove(mouseData, parentPos + pos);

    if(posIsOnButton((sf::Vector2f) mouseData.position, parentPos))
    {
        if(state == State::OFF)
        {
            state = HOVERED;
        }
    }
    else
    {
        state = State::OFF;
    }
}
bool TextButton::handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos)
{
    UIComponent::handleMouseButtonChange(button, position, pressed, parentPos + pos);

    bool catchChange = false;
    //If this is a left click
    if(button == sf::Mouse::Button::Left)
    {
        if(this->posIsOnButton(position, parentPos))
        {
            if(pressed == true)
            {
                state = State::PRESSED;

                //Notify the parent of this change
                UIComponent::onInputChange(this);
                    
                std::cout << "pressed" << std::endl;
            }
            else
            {
                if(state == State::PRESSED)
                {
                    //Set the state to clicked
                    state = State::CLICKED;
                    
                    //Notify the parent of the change
                    UIComponent::onInputChange(this);

                    //Set state to hovered
                    state = State::HOVERED;

                    std::cout << "clicked" << std::endl;
                }
            }

            catchChange = true;
        }
    }

    return catchChange;
}
