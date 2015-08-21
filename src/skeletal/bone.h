#ifndef H_SKELE_BONE
#define H_SKELE_BONE

#include <memory>
#include <vector>
#include <math.h>

#include "../vec2f.h"

class Bone
{
public:
    Bone();
    Bone(float length, float angle);
    
    void create(float length, float angle);

    void setAngle(float angle);
    void setLength(float length);
    void setName(std::string name);
    void setParent(Bone* parent);
    void addChild(std::unique_ptr<Bone> bone); //TODO: Change raw pointer to unique_ptr

    Vec2f getTip();
    float getWorldAngle();
private:
    void calculateGlobalValues();

    Bone* parent;

    std::vector< std::unique_ptr< Bone > > children;

    std::string name;

    float length;
    float angle;
    float worldAngle;

    Vec2f tip;
    Vec2f localTip;
};
#endif
