#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <Windows.h>

#include "State.hpp"
#include "InGame.hpp"
#include "MapSelect.hpp"
#include "GameMenu.hpp"

class Engine {
private:
    // Main game
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    std::vector<State*> states;
    State *currentState;
    unsigned int framerateLimit;
    float dt;

    // Loading screen
    sf::RenderWindow *loadingWindow;
    sf::Texture textureLoading;
	sf::Sprite spriteLoading;
	float spriteScale;
	bool doneLoading;

    #ifdef DEBUG
    uint32_t appWidth, appHeight;
    float tt;
    void debugManager();
    #endif // DEBUG
    
private:
    void getMainDirectory();
    void updateDeltaTime();
    void updateSFMLEvents();
    void stateManager();
    void update();
    void render();
    void startGameResources();
    void loadStatesAssets();
	void loadingScreen();
	void init();

public:
    Engine();
    ~Engine();
    void run();
};

#endif // ENGINE_H