#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <direct.h>

float deltaTime = 0.0f;
#include "Core.hpp"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow){
	std::cout << std::boolalpha << std::endl;
	getMainDirectory();
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Where's Wally?", sf::Style::Close | sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	sf::Clock animationClock;
	while (window.isOpen()) {
		if (!GameClockStruct::ClockRunning)
			GameClockStruct::gameClockTimer.restart();
		deltaTime = animationClock.restart().asSeconds();
		window.clear();
		if (MenuActive && !InGameActive) 
			GameMenu(&window);

		else if (InGameActive && !MenuActive) 
			InGame(&window);
		
		gameEvents(&window);
		window.display();
	}
	return EXIT_SUCCESS;
}