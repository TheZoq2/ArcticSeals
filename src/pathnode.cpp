#include "pathnode.h"

PathNode::PathNode(Vec2f position, Platform* platform)
{
    this->position = position;
    this->platform = platform;
}

void PathNode::addLink(PathNode* other, LinkType type)
{
    links.push_back(Link(type, other));
}

Vec2f PathNode::getPosition()
{
    return position;
}
