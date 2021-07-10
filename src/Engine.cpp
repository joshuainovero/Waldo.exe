#include "Engine.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <fstream>
#include <json/json.h>
#include <unistd.h>
#include <Tlhelp32.h>

#include <iostream>

void Engine::loadStatesAssets(){
	this->states.push_back(new GAMEMENU);
	this->states.push_back(new MAPSELECT);
	this->states.push_back(new INGAME);
	this->doneLoading = true;
}

void Engine::loadingScreen(){
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

		if (this->doneLoading)
			this->loadingWindow->close();
	}
}

void Engine::init(){
	std::thread threadLoadAssets(&Engine::loadStatesAssets, this);
	this->loadingScreen();
	threadLoadAssets.join();
}

void Engine::startGameResources(){
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
    this->init();
}

Engine::Engine(){
    #ifdef DEBUG
    this->debugManager();
    this->tt = 0.0f;
    this->appWidth = sf::VideoMode::getDesktopMode().width;
    this->appHeight = sf::VideoMode::getDesktopMode().height;
    #endif // DEBUG
    this->startGameResources();
	std::ofstream emptySpriteFile("Assets/sprite.png", std::ios::binary);
    currentState = states.at(0);
    this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Where's Wally?", sf::Style::Close | sf::Style::Fullscreen);
    // this->window->setVerticalSyncEnabled(false);

    std::ifstream fileDataJson("Data/data.json");
		Json::Value data;
		Json::Reader reader;
		reader.parse(fileDataJson, data);
	fileDataJson.close();
    this->framerateLimit = data["app-properties"]["framerate-limit"].asUInt();
    this->window->setFramerateLimit(this->framerateLimit);
    this->dt = 0.0f;
    this->getMainDirectory();
    
}

Engine::~Engine(){
    delete this->window;
	std::ifstream fileDataJson1("Data/data.json");
		Json::Value data1;
		Json::Reader reader;
		reader.parse(fileDataJson1, data1);
	fileDataJson1.close();
    Json::Value data = data1;
    data["gameplay-status"]["gotomap"]["triggered"] = false;
    std::ofstream fileDataJson("Data/data.json");
    Json::StyledWriter styledwriter;
    fileDataJson << styledwriter.write(data);
    fileDataJson.close();
}

void Engine::updateSFMLEvents(){
    while (this->window->pollEvent(this->sfEvent)){
		switch (this->sfEvent.type) {
			case sf::Event::Closed:
				this->window->close(); 
			break;
			default: break;
		}
    }
}

void Engine::update(){
	// if (!GameClockStruct::ClockRunning)
	// 	GameClockStruct::gameClockTimer.restart();
        
    #ifdef DEBUG
    this->tt += this->dt;
    if (this->tt >= 1.5) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A); std::cout << "Screen Resolution ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F); std::cout << "(" << this->appWidth << "x" << this->appHeight << ") , ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E); std::cout << "FPS (limit : " + std::to_string(this->framerateLimit) + ")";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
        std::cout << " : " << 1.0f / this->dt << std::endl;
        tt = 0.0f;
        
    }
    #endif // DEBUG
    
    this->dt = dtClock.restart().asSeconds();
    this->updateSFMLEvents();
    this->stateManager();
}
void Engine::stateManager(){
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
void Engine::render(){
    this->window->clear();
	currentState->run(this->window, this->dt);
    this->window->display();
}


void Engine::run(){
    while (this->window->isOpen()){
        this->update();
        this->render();
    }
}

void Engine::getMainDirectory(){
    char tmp[256];
    getcwd(tmp, 256);
	std::string path = tmp;

		std::ifstream fileDataJson1("Data/data.json");
		Json::Value dataV;
		Json::Reader reader;
		reader.parse(fileDataJson1, dataV);
	fileDataJson1.close();
    Json::Value data = dataV;
    data["app-properties"]["main-directory"] = path;

    std::ofstream fileDataJson("Data/data.json");
	    Json::StyledWriter styledwriter;
	    fileDataJson << styledwriter.write(data);
	fileDataJson.close();
}

#ifdef DEBUG
void Engine::debugManager(){
    std::ifstream fileDataJson("Data/data.json");
		Json::Value data;
		Json::Reader reader;
		reader.parse(fileDataJson, data);
	fileDataJson.close();
	system(std::string("title Waldo Debug " + data["app-properties"]["localversion"].asString()).c_str());
    RECT r;
    GetWindowRect(GetConsoleWindow(), &r);
    MoveWindow(GetConsoleWindow(), r.left, r.top, 800, 600, TRUE);
}
#endif 
