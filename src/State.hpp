#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <json/json.h>
#include <fstream>
#include "EDassets.hpp"

class State{
protected:
    sf::Texture arrowTexture;
    sf::Texture handTexture;
    sf::Sprite arrowSprite;
    sf::Sprite handSprite;
    sf::SoundBuffer globalClickBuffer;
    sf::Sound globalClickSound;
    Json::Value getDataJson();

    float fullScreenSpriteScale;
    float scaleArrow;
    float maxResolution;

    bool appInFocus(sf::RenderWindow* app);
    float getFullScreenSpriteScale();
    float getScaleArrow();
    void createSprite(sf::Texture &textureP, sf::Sprite &spriteP, const std::string &pathF);
    virtual void loadResources() = 0;
public:
    std::string switchingState = "None";
    bool mouseDown = false;
    sf::Music *currentMusic;
    State();
    virtual ~State();
    virtual void notInStateProcess() = 0;
    virtual void run(sf::RenderWindow *window, const float &dtArg) = 0;
    void stopCurrentMusicPlaying();
};
