#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>


#include "Scales.hpp"
#include "Labels.hpp"
#include "MapProperties.hpp"
#include "loadAssets.hpp"
#include "GameStates.hpp"
#include "GameMenu.hpp"
#include "InGame.hpp"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow) {
	std::cout << "Debug Console" << std::endl;
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Where's Wally?", sf::Style::Close | sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	//std::cout << sf::VideoMode::getDesktopMode().width << " " << sf::VideoMode::getDesktopMode().height << std::endl;
	while (window.isOpen()) {
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			switch (windowEvent.type) {
			case sf::Event::TextEntered:
				std::cout << char(windowEvent.text.unicode);
				if (windowEvent.text.unicode == 27) {
					window.close();
				}
				break;
			}
		}
		//std::cout << sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height << std::endl;
		window.clear();
		if (MenuActive && !InGameActive) {
			GameMenu(&window);
		}

		else if (InGameActive && !MenuActive) {
			InGame(&window);
		}

		//window.draw(mybutton.returnButton());
		// if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		// 	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		// 	std::cout << mousePos.x << " " << mousePos.y << std::endl;
		// }
		
		window.display();


	}

	return EXIT_SUCCESS;
}