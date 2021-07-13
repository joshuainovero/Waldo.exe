#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <Windows.h>
#include "State.hpp"
#include "InGame.hpp"
#include "MapSelect.hpp"
#include "GameMenu.hpp"

class GameResources{
public:
    GameResources();
    ~GameResources() = default;
    void stateManager();
    std::vector<State*> states;
    State *currentState;

private:
    // Temporary members and methods for loading
    sf::RenderWindow *loadingWindow;
    sf::Texture textureLoading;
	sf::Sprite spriteLoading;
	float spriteScale;
	bool doneLoading;
    void startWindowScreen();
    void loadStatesAssets();
	void loadingScreen();
    void init();

};