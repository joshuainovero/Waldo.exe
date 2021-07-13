#include "GameResources.hpp"
#include <thread>

void GameResources::loadStatesAssets(){
	this->states.push_back(new GAMEMENU);
	this->states.push_back(new MAPSELECT);
	this->states.push_back(new INGAME);
	this->doneLoading = true;
}

void GameResources::loadingScreen(){
	while (this->loadingWindow->isOpen()){
		sf::Event evnt;
		while (this->loadingWindow->pollEvent(evnt)){
			if (evnt.type == sf::Event::Closed){
				this->loadingWindow->close();
			}
		}
		this->loadingWindow->clear();
		this->loadingWindow->draw(spriteLoading);
		this->loadingWindow->draw(BARUI::barlimit);
		this->loadingWindow->draw(BARUI::barload);
		this->loadingWindow->display();

		if (this->doneLoading){
			this->loadingWindow->close();
            // delete this->loadingWindow;
        }
	}
}

void GameResources::init(){
	std::thread threadLoadAssets(&GameResources::loadStatesAssets, this);
	this->loadingScreen();
	threadLoadAssets.join();
}

void GameResources::startWindowScreen(){
    this->loadingWindow = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width * 0.50, sf::VideoMode::getDesktopMode().height * 0.50), "Where's Wally?", sf::Style::None);

    this->spriteScale = (sf::VideoMode::getDesktopMode().height * 0.50) / 1080.0f;

    EDassets::decryptFile("Assets/004/004-ld");
    EDassets::decryptFile("Assets/004/004-ld");
	increaseBar(BARUI::barload);

	this->textureLoading.loadFromFile("Assets/sprite.png");
	this->spriteLoading.setTexture(textureLoading);
	increaseBar(BARUI::barload);

	this->spriteLoading.setScale(spriteScale, spriteScale);

    this->doneLoading = false;
    BARUI::SETPOSITION(*loadingWindow);
}

void GameResources::stateManager(){
    if (currentState->switchingState == "Menu"){
        currentState->switchingState = "None";
        currentState = states.at(0);
        currentState->mouseDown = true;
    }
    else if (currentState->switchingState == "MapSelect"){
        currentState->switchingState = "None";
        currentState = states.at(1);
        currentState->mouseDown = true;
    }
    else if (currentState->switchingState == "InGame"){
        currentState->switchingState = "None";
        currentState = states.at(2);
        currentState->mouseDown = true;
    }

    // Not in state process
    if (currentState != states.at(2)){
        states.at(2)->notInStateProcess();
    }
    if (currentState != states.at(1) && currentState != states.at(0)){
        states.at(0)->currentMusic->stop();
    }
}

GameResources::GameResources(){
	this->startWindowScreen();
	this->init();
	this->currentState = this->states.at(0);
	std::ofstream emptySpriteFile("Assets/sprite.png", std::ios::binary);
}
