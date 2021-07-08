#include "State.hpp"
#include <Windows.h>
std::vector<State*> State::states;
State *State::currentState;
sf::Texture State::arrowTexture;
sf::Texture State::handTexture;
sf::Sprite State::arrowSprite;
sf::Sprite State::handSprite;
sf::SoundBuffer State::globalClickBuffer;
sf::Sound State::globalClickSound;
float State::fullScreenSpriteScale;
float State::scaleArrow;

float State::getFullScreenSpriteScale() { return State::fullScreenSpriteScale; }
float State::getScaleArrow() { return State::scaleArrow; }

void State::createSprite(sf::Texture &textureP, sf::Sprite &spriteP, const std::string &pathF){
    EDassets::decryptFile(pathF);
    increaseBar(BARUI::barload);
    textureP.loadFromFile("Assets/sprite.png");
    spriteP.setTexture(textureP);
    increaseBar(BARUI::barload);
}

void State::stopCurrentMusicPlaying(){
    currentMusic->stop();
}

// void State::loadResources() {

// }

State::~State(){
    for (size_t i = 0; i < State::states.size(); ++i){
        delete State::states[i];
    }
    State::states.clear();
}