#ifndef H_GROUND_COMPONENT
#define H_GROUND_COMPONENT

#include "DrawableComponent.h"

namespace zen
{
    
    class GroundComponent : public DrawableComponent
    {
    public:
        GroundComponent() = default;
        
        void load(std::string filename);
        void draw(sf::RenderTarget* target) override;

        std::vector<Vec2f>* getPoints();

    private:
        void generateVertexArray();
        sf::VertexArray vertecies;

        std::vector<Vec2f> points;
    };
} /* zen */ 

#endif
