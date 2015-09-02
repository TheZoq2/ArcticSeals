#include "pathnode.h"

PathNode::PathNode(Vec2f position)
{
    this->position = position;
}

void PathNode::addLink(PathNode* other, LinkType type)
{
    links.push_back(Link(type, other));
}
