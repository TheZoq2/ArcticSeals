#include "pathfinder.h"

const float Pathfinder::MAX_NODE_DISTANCE = 400;

Pathfinder::Pathfinder(EntityGroup* group)
{
    this->entityGroup = group;
}

/////////////////////////////////////////////////////////////////////
//                      Private methods
/////////////////////////////////////////////////////////////////////

void Pathfinder::generateLinks()
{
    nodes.clear();

    //Going through the platforms and getting all the path nodes
    for(auto it : entityGroup->getPlatforms())
    {
        for(auto node : it.platform->getPathNodes())
        {
            nodes.push_back(node);
        }
    }

    //Generating links between all the platforms
    for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        for(auto node = it; it != nodes.end(); ++it)
        {
            //Make sure the two nodes aren't on the same platform
            if(node->getPlatform() != it->getPlatform())
            {
                float distance = ((Vec2f) (node->getPosition() - it->getPosition())).length();

                //If this node should be jumpable to
                if(distance < MAX_NODE_DISTANCE)
                {
                    //TODO: If the pathfinding is too slow:
                    //Checking if you can jump to or from this node or just fall onto it
                    
                    it->addLink(&*node, PathNode::LinkType::JUMP);
                    node->addLink(&*it, PathNode::LinkType::JUMP);
                }
            }
        }
    }
}

