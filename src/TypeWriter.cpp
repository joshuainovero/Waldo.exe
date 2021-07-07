#include "TypeWriter.hpp"

TypeWriter::TypeWriter(std::string textContent, float switchTime, float posX, float posY, uint32_t sizeChar){
    sf::Vector2f twScreenResolution(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
    this->switchTime = switchTime;
    this->textContent = textContent;
    font.loadFromFile("Assets/Fonts/Crossten-ExtraBold.ttf");
    text.setFont(font);
    text.setString(typeWriterStr);
    text.setFillColor(sf::Color::Black);
    currentPosition = 0;
    typeWriterStr = "";
    text.setCharacterSize(twScreenResolution.y * sizeChar/768);
    text.setPosition(sf::Vector2f(twScreenResolution.x * posX/1366, twScreenResolution.y * posY/768));
    
}
void TypeWriter::updateText(float passedDeltaTime){
    if (typeWriterStr.length() <= textContent.length()){
        totalTime += passedDeltaTime;
        if (totalTime >= switchTime){
            totalTime -= switchTime;
            typeWriterStr += textContent[currentPosition];
            text.setString(typeWriterStr);
            currentPosition++;
        }
    }
}

void TypeWriter::resetTypeWriter(){
    currentPosition = 0;
    typeWriterStr = "";
}

void TypeWriter::drawTypeWriter(sf::RenderWindow *window){
    window->draw(text);
}