#include "imglist.h"

using namespace zui;

ImgList::ImgList(std::vector<std::pair<std::string, std::string>> elements, Vec2f pos, Vec2f size, std::string name)
    :UIComponent(pos), InputComponent(name)
{
    this->selectedElement = NULL;
    this->size = size;
    this->bgColor = sf::Color(150,150,150);
    this->value = "";

    Vec2f inputPos(padding, padding);
    for(auto& it : elements)
    {
        float nextX = inputPos.x + imgSize + padding;
        if(nextX > size.x)
        {
            inputPos.x = 0;
            inputPos.y += padding + imgSize;
        }
        
        //Create the input element
        ImgListElement* newElement = new ImgListElement(it.first, it.second, inputPos, Vec2f(imgSize, imgSize));

        newElement->setParent(this);

        this->listElements.push_back(std::unique_ptr<ImgListElement>(newElement));

        inputPos.x += padding + imgSize;
    }

    //Creating the background shape
    bgShape.setSize(size);
    bgShape.setFillColor(bgColor);

    //Button parameters
    TextButton::ButtonColor buttonColor;
    buttonColor.defaultColor = sf::Color(0,0,255);
    buttonColor.hoverColor = sf::Color(150,150,255);
    buttonColor.pressColor = sf::Color(100,100,255);
    Vec2f buttonSize(120,40);

    okButton = std::unique_ptr<TextButton>(new TextButton("OK_BUTTON", Vec2f(padding, size.y - buttonSize.y - padding), buttonSize, buttonColor,"OK"));
    okButton->setParent(this);
}

void ImgList::drawSelf(sf::RenderWindow* window, Vec2f actualPos)
{
    bgShape.setPosition(actualPos);
    window->draw(bgShape);

    okButton->draw(window, actualPos);

    for(auto& it : listElements)
    {
        it->draw(window, actualPos);
    }
}

void ImgList::onInputChange(InputComponent* component)
{
    if(component->getName().compare(ImgListElement::DEFAULT_NAME) == 0)
    {
        if(component->boolValue() == true)
        {
            //Unselect the old element
            if(selectedElement != NULL)
            {
                this->selectedElement->setValue(false);
            }

            this->selectedElement = component;
            this->value = ((ImgListElement*) component)->getValueName();
        }
    }
    else if(component->getName().compare("OK_BUTTON"))
    {
        if(component->boolValue() == true)
        {
            if(parent != NULL)
            {
                //notify parents of this change
                parent->onInputChange(this);
            }
        }
    }
    else
    {
        notifyListeners(component);

        //This is a component that is unrelated to the imgList, tell the parent about this change.
        if(parent != NULL)
        {
            //parent->onInputChange(component);
            UIComponent::onInputChange(this);
        }
    }
}
std::string ImgList::stringValue()
{
    return this->value;
}

void ImgList::handleMouseMove(MouseData data, Vec2f parentPos)
{
    Vec2f actualPos = pos + parentPos;
    
    UIComponent::handleMouseMove(data, actualPos);

    okButton->handleMouseMove(data, actualPos);
    for(auto& it : listElements)
    {
        it->handleMouseMove(data, actualPos);
    }
}
bool ImgList::handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos)
{
    Vec2f actualPos = pos + parentPos;

    bool block = UIComponent::handleMouseButtonChange(button, position, pressed, actualPos);
    
    if(block == false)
    {
        for(auto& it : listElements)
        {
            if(it->handleMouseButtonChange(button, position, pressed, actualPos))
            {
                block = true;
            }
        }
    }

    return block;
}

void ImgList::setBackgroundColor(sf::Color bgColor)
{
    this->bgColor = bgColor;
    this->bgShape.setFillColor(bgColor);
}
