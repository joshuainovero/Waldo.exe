#ifndef STATIC_OBJ_ANIMATION_H_
#define STATIC_OBJ_ANIMATION_H_
#include <SFML/Graphics.hpp>

class StaticObjAnimation {
public:
    StaticObjAnimation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
    StaticObjAnimation(){}
    virtual void Update(int row, float deltaTime) = 0;
public:
    sf::IntRect uvRect;
    int currentRow = 0;
protected:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};

#endif // STATIC_OBJ_ANIMATION_H_

