#include "Engine.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <fstream>
#include <json/json.h>
#include <unistd.h>
#include <Tlhelp32.h>

#ifdef DEBUG
#include <iostream>
#endif

Engine::Engine():resources(){
    #ifdef DEBUG
    this->debugManager();
    this->tt = 0.0f;
    this->appWidth = sf::VideoMode::getDesktopMode().width;
    this->appHeight = sf::VideoMode::getDesktopMode().height;
    #endif // DEBUG
    this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Where's Wally?", sf::Style::Close | sf::Style::Fullscreen);
    
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
    this->resources.stateManager();
}

void Engine::render(){
    this->window->clear();
	this->resources.currentState->run(this->window, this->dt);
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
