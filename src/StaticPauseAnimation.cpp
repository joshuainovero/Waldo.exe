#include "StaticPauseAnimation.hpp"

StaticPauseAnimation::StaticPauseAnimation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) : 
    StaticObjAnimation(texture, imageCount, switchTime) { isStop = false; }

void StaticPauseAnimation::resetState(){
    isStop = false;
    currentImage.x = 0;
    currentRow = 0;
}

void StaticPauseAnimation::Update(int row, float deltaTime){
    if (!isStop){
        currentImage.y = row;
        totalTime += deltaTime;
        if (totalTime >= switchTime){
            totalTime -= switchTime;
            currentImage.x++;
            if (currentImage.x >= imageCount.x){
                currentImage.x = 0;
                currentRow++;
                currentImage.y = currentRow;
                if (currentImage.y >= imageCount.y){
                    currentImage.x = 4;
                    currentImage.y = 2;
                    isStop = true;
                }
            }
        }

    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    
}