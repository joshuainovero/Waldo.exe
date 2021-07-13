#include "StaticCircleAnimation.hpp"

StaticCircleAnimation::StaticCircleAnimation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) : 
    StaticObjAnimation(texture, imageCount, switchTime) { shrink = false; }

void StaticCircleAnimation::Update(int row, float deltaTime){
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
