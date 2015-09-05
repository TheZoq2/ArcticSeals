#ifndef H_PATHNODE
#define H_PATHNODE

#include "vec2f.h"

class Platform;

class PathNode
{
public:
    enum LinkType
    {
        LOCAL,
        JUMP
    };
    struct Link
    {
        Link(LinkType type, PathNode* otherNode, Platform* platform)
        {
            this->type = type;
            this->otherNode = otherNode;
        }
        LinkType type;
        PathNode* otherNode;
    };

    PathNode(Vec2f position, Platform* parent);

    void addLink(PathNode* other, LinkType type);

    Vec2f getPosition();
private:
    Vec2f position;

    std::vector<Link> links;

    Platform* parent;
};
#endif
