#ifndef H_PATHNODE
#define H_PATHNODE

#include "vec2f.h"

class PathNode
{
public:
    enum LinkType
    {
        LOCAL,
        JUMP
    }
    struct Link
    {
        Link(LinkType type, PathNode* otherNode)
        {
            this->type = type;
            this->otherNode = otherNode;
        }
        LinkType type;
        PathNode* otherNode;
    };

    PathNode(Vec2f position);

    void addLink(PathNode* other, LinkType type);
private:
    Vec2f position;

    std::vector<Link> links;
};
#endif
