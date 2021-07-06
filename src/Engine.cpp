#include "Engine.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>

Engine::Engine(){
	std::ofstream emptySpriteFile("Assets/sprite.png", std::ios::binary);
    State::currentState = State::states.at(0);
    this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Where's Wally?", sf::Style::Close | sf::Style::Fullscreen);
    this->window->setVerticalSyncEnabled(true);
    this->dt = 0.0f;
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
	if (!GameClockStruct::ClockRunning)
		GameClockStruct::gameClockTimer.restart();
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
