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
bool mouseDown = true;
#include "Core.hpp"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow){
	windowLoad();
	getMainDirectory();
	std::ofstream emptySpriteFile("Assets/sprite.png", std::ios::binary);
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Where's Wally?", sf::Style::Close | sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	sf::Clock animationClock;
	while (window.isOpen()) {
		if (!GameClockStruct::ClockRunning)
			GameClockStruct::gameClockTimer.restart();
		deltaTime = animationClock.restart().asSeconds();
		window.clear();
		if (MenuActive && !InGameActive && !MapSelectActive) 
			GameMenu(&window);
		else if (MapSelectActive && !MenuActive && !InGameActive)
			MapSelection(&window);
		else if (InGameActive && !MenuActive && !MapSelectActive) 
			InGame(&window);
		
		gameEvents(&window);
		window.display();
	}
	return EXIT_SUCCESS;
}