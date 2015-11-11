#include "DrawableComponent.h"

#include <fstream>

#include "GroundComponent.h"
#include "../entity.h"

using namespace zen;

void GroundComponent::load(std::string filename) 
{
    //Start reading from the file
    std::fstream fs(filename, std::fstream::in | std::fstream::out);


    //Read all the coordinates from the file
    Vec2f coords;
    while(fs >> coords.x && fs >> coords.y)
    {
        //Add the points to the list
        points.push_back(coords);
    }

    //Done using the file, close it
    fs.close();

    generateVertexArray();
}

void GroundComponent::draw(sf::RenderTarget* target)
{
    TransformComponent* transComp = owner->getTransformComponent();

    //Render state for setting transforms and textures
    sf::RenderStates state;
    state.transform.translate(transComp->getPosition());
    state.transform.rotate(transComp->getAngle());
    state.transform.scale(transComp->getScale());

    target->draw(vertecies, state);
}

std::vector<Vec2f>* GroundComponent::getPoints()
{
    return &points;
}


//////////////////////////////////////////////////////////////////////////////////////////
//								Private members
//////////////////////////////////////////////////////////////////////////////////////////

void GroundComponent::generateVertexArray() 
{
    for(auto& it : points)
    {
        vertecies.append(it);
    }
}



