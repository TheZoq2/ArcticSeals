#ifndef H_PLATFORM
#define H_PLATFORM

#include <SFML/Graphics.hpp>

class Platform
{
public:
    void create(sf::Vector2f pos1, sf::Vector2f pos2)
private;
    sf::Vector2f positions[2];
    
    struct CollisionResult
    {
        bool collision;
        sf::Vector2f position;
    };

    //Returns the point
    sf::Vector2f getVerticalIntersection(float x, float startY, float endY);
};
#endif
