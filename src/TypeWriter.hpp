#pragma once
#include <SFML/Graphics.hpp>

class TypeWriter{
private:
    sf::Text text;
    sf::Font font;
    float totalTime;
    float switchTime;
    size_t currentPosition;
    
public:
    std::string textContent;
    std::string typeWriterStr;
    TypeWriter(std::string textContent, float switchTime, float posX, float posY, uint32_t sizeChar);
    void updateText(float passedDeltaTime);
    void drawTypeWriter(sf::RenderWindow *window);
    void resetTypeWriter();
    void tcSetString(const std::string &str) {textContent = str;};
};
