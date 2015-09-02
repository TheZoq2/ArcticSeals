#include "platform.h"

const float Platform::PATH_NODE_DISTANCE = 50;

void Platform::create(Vec2f pos)
{
    this->pos = pos;
}
void Platform::draw(sf::RenderWindow* window)
{
    for(auto it : lines)
    {
        it.draw(window);
    }

    sf::CircleShape nodeShape(10);
    nodeShape.setFillColor(sf::Color(0,0,0,0));
    nodeShape.setOutlineColor(sf::Color(255,255,255,255));
    nodeShape.setOutlineThickness(2);
    nodeShape.setOrigin(10,10);
    for(auto it : pathNodes)
    {
        nodeShape.setPosition(it);
        window->draw(nodeShape);
    }
}

void Platform::addPoint(Vec2f point)
{
    std::vector<Vec2f>::iterator insertPos = points.end();
    //Checking where the point should go
    for(std::vector<Vec2f>::iterator it = points.begin(); it != points.end(); it++)
    {
        if(point.x < it->x)
        {
            insertPos = it;
            break;
        }
    }

    points.insert(insertPos, point);

    generateLines();
    generatePathNodes();
}
void Platform::addPoint(float x, float y)
{
    addPoint(Vec2f(x, y));
}

Line::IntersectResult Platform::getCollision(Line* otherLine)
{
    Line::IntersectResult intersect;
    intersect.intersected = false;

    //Going through all the lines to check for collision
    for(auto it : lines)
    {
        intersect = it.getIntersect(otherLine);
        if(intersect.intersected == true)
        {
            return intersect;
        }
    }
    
    return intersect;
}
float Platform::getLocalX(float globalX)
{
    return globalX - pos.x;
}
bool Platform::xIsOnPlatform(float localX)
{
    return localX >= points.front().x && localX <= points.back().x;
}
Vec2f Platform::getGlobalPos(float localX)
{
    Vec2f result(0,0);

    float globalX = localX + pos.x;

    //Make sure the pos is actually on the platform
    if(xIsOnPlatform(localX) == false)
    {
        fprintf(stderr, "Local x coordinate is not on platform in Platform::getGlobalPos()\n");
    }

    //Loop through the lines to find the correct position
    for(auto it : lines)
    {
        if(globalX >= it.getPosition(0).x && globalX <= it.getPosition(1).x)
        {
            result.x = globalX;
            result.y = it.calculateYValue(globalX);
        }
    }
    
    return result;
}

void Platform::setPosition(Vec2f pos)
{
    this->pos = pos;

    generateLines();
    generatePathNodes();
}


//////////////////////////////////////////////////////////////////////////////
//  Private methods
//////////////////////////////////////////////////////////////////////////////

void Platform::generateLines()
{
    lines.clear();

    //If there is only one point, a line can't be generated
    if(points.size() <= 1)
    {
        return;
    }

    for(unsigned int i = 0; i < points.size() - 1; i++)
    {
        lines.push_back(Line(points.at(i) + pos, points.at(i + 1) + pos));
    }
}
void Platform::generatePathNodes()
{
    pathNodes.clear();

    //Create path nodes that are adequetly placed along the platform
    for(float nodePos = points[0].x; nodePos < points.back().x; nodePos += PATH_NODE_DISTANCE)
    {
        pathNodes.push_back(getGlobalPos(nodePos));
    }
    //Put one node on the edge of the platform which might not be reached otherwise
    pathNodes.push_back(getGlobalPos(points.back().x));
}
