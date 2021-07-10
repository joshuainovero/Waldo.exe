#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <json/json.h>
#include <fstream>
#include "EDassets.hpp"

class State{
friend class Engine;
protected:
    sf::Texture arrowTexture;
    sf::Texture handTexture;
    sf::Sprite arrowSprite;
    sf::Sprite handSprite;
    sf::SoundBuffer globalClickBuffer;
    sf::Sound globalClickSound;

    float fullScreenSpriteScale;
    float scaleArrow;
    float getFullScreenSpriteScale();
    float getScaleArrow();
    float maxResolution;
    sf::Music *currentMusic;
    bool appInFocus(sf::RenderWindow* app);
public:
    std::string switchingState = "None";
    bool mouseDown = false;
    State();

    void createSprite(sf::Texture &textureP, sf::Sprite &spriteP, const std::string &pathF);
    void stopCurrentMusicPlaying();
    Json::Value getDataJson();

    virtual ~State();
    virtual void loadResources() = 0;
    virtual void notInStateProcess() = 0;
    virtual void run(sf::RenderWindow *window, const float &dtArg) = 0;
};
