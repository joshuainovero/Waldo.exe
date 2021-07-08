#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MapProperties.hpp"

class State{
protected:
    static sf::Texture arrowTexture;
    static sf::Texture handTexture;
    static sf::Sprite arrowSprite;
    static sf::Sprite handSprite;
    static sf::SoundBuffer globalClickBuffer;
    static sf::Sound globalClickSound;

    static float fullScreenSpriteScale;
    static float scaleArrow;
    static float getFullScreenSpriteScale();
    static float getScaleArrow();
    static constexpr float maxResolution = 1080;
    sf::Music *currentMusic;
public:
    static std::vector<State*> states;
    static State *currentState;
    State() = default;

    void createSprite(sf::Texture &textureP, sf::Sprite &spriteP, const std::string &pathF);
    void stopCurrentMusicPlaying();

    virtual ~State();
    virtual void loadResources() = 0;
    virtual void run(sf::RenderWindow *window, const float &dtArg) = 0;
};
