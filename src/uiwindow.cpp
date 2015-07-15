#include "uiwindow.h"

UIWindow::UIWindow()
{}
UIWindow::~UIWindow()
{}

void UIWindow::create(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
    this->size = size;
    this->color = color;
    UIComponent::pos = pos;
    
    this->shape.setSize(size);
    this->shape.setFillColor(color);
    
}

void UIWindow::setPosition(sf::Vector2f pos)
{
    UIComponent::setPosition(pos);
    this->shape.setPosition(pos);
}

void UIWindow::drawSelf(sf::RenderWindow* window, sf::Vector2f totalPos)
{
    this->shape.setPosition(totalPos);
    window->draw(shape);
    
}
