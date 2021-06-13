#include "StaticObjAnimation.hpp"
#include <iostream>
static bool shrink = true;
StaticObjAnimation::StaticObjAnimation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime){
    this->imageCount = imageCount;
    this->switchTime = switchTime;

    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

void StaticObjAnimation::Update(int row, float deltaTime){
    currentImage.y = row;
    totalTime += deltaTime;
    if (totalTime >= switchTime){
        totalTime -= switchTime;
        if (currentImage.x == 0)
            shrink = true;
        else if (currentImage.x >= imageCount.x - 1)
            shrink = false;
        if (shrink){
            currentImage.x++;
        }
        else if(!shrink) {
            currentImage.x--;
        } 
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

