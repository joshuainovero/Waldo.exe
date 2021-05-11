#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>

bool appInFocus(sf::RenderWindow* app)
{
        if(app == NULL)
                return false;

        HWND handle = app->getSystemHandle();
        bool one = handle == GetFocus();
        bool two = handle == GetForegroundWindow();

        if(one != two)
        {
                SetFocus(handle);
                SetForegroundWindow(handle);
        }

        return one && two;
}

#include "Core.hpp"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow) {
	//std::cout << "Debug Console" << std::endl;
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Where's Wally?", sf::Style::Close | sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	//std::cout << sf::VideoMode::getDesktopMode().width << " " << sf::VideoMode::getDesktopMode().height << std::endl;
	while (window.isOpen()) {
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			switch (windowEvent.type) {
			case sf::Event::TextEntered:
				if (windowEvent.text.unicode == 27)
					window.close(); break;
			case sf::Event::Closed:
				window.close(); break;
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