#include "bone.h"

using namespace zen;

Bone::Bone()
{
    parent = NULL;
    length = 0;
    angle = 0;
}
Bone::Bone(float length, float angle)
    :Bone()
{
    create(length, angle);
}

void Bone::create(float length, float angle)
{
    this->length = length;
    this->angle = angle;
    
    calculateGlobalValues();
}

void Bone::setAngle(float angle)
{
    this->angle = angle;
    calculateGlobalValues();
}
void Bone::setLength(float length)
{
    this->length = length;
    calculateGlobalValues();
}
void Bone::setName(std::string name)
{
    this->name = name;
}
void Bone::setParent(Bone* parent)
{
    this->parent = parent;
}
void Bone::addChild(std::unique_ptr<Bone> bone)
{
    bone->parent = this;
    this->children.push_back(std::move(bone));
}

Vec2f Bone::getTip()
{
    return tip;
}
float Bone::getWorldAngle()
{
    return worldAngle;
}

/////////////////////////////////////////////////////////////////////////////////////////
//                      Private methods
/////////////////////////////////////////////////////////////////////////////////////////

void Bone::calculateGlobalValues()
{
    float parentAngle = 0;
    Vec2f parentTip(0,0);

    if(parent != NULL)
    {
        parentAngle = parent->getWorldAngle();
        parentTip = parent->getTip();
    }
    //Calculating the global angle
    this->worldAngle = parentAngle + angle;

    //calculating the tip of this bone
    tip.x = cos(worldAngle) * length;
    tip.y = sin(worldAngle) * length;

    //Notify all the children of this change
    for(auto& it : children)
    {
        it->calculateGlobalValues();
    }
}
