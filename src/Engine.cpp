#include "Engine.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <Windows.h>

#include <iostream>

Engine::Engine(){
	std::ofstream emptySpriteFile("Assets/sprite.png", std::ios::binary);
    State::currentState = State::states.at(0);
    this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Where's Wally?", sf::Style::Close | sf::Style::Fullscreen);
    // this->window->setVerticalSyncEnabled(false);
    this->window->setFramerateLimit(120);
    
    this->dt = 0.0f;
    #ifdef DEBUG
    this->tt = 0.0f;
    #endif // DEBUG
}

Engine::~Engine(){
    delete this->window;
}

bool Engine::appInFocus(sf::RenderWindow* app){
    if(app == NULL)
        return false;

    HWND handle = app->getSystemHandle();
    bool one = handle == GetFocus();
    bool two = handle == GetForegroundWindow();

    if(one != two){
        SetFocus(handle);
        SetForegroundWindow(handle);
    }

    return one && two;
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
	if (!GameClockStruct::ClockRunning)
		GameClockStruct::gameClockTimer.restart();
        
    #ifdef DEBUG
    this->tt += this->dt;
    if (this->tt >= 1.5) {
        std::cout << 1.0f / dtClock.getElapsedTime().asSeconds() << std::endl;
        tt = 0.0f;
    }
    #endif // DEBUG
    
    this->dt = dtClock.restart().asSeconds();
    this->updateSFMLEvents();
}

void Engine::render(){
    this->window->clear();
	State::currentState->run(this->window, this->dt);
    this->window->display();
}


void Engine::run(){
    while (this->window->isOpen()){
        this->update();
        this->render();
    }
}

bool Engine::mouseDown = false;
