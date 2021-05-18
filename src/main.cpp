#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <direct.h>

#include "Core.hpp"

struct CMDBuildManager{ ~CMDBuildManager(){system("TASKKILL /F /IM cmd.exe 2>NULL");}};
CMDBuildManager cmd;
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow){
	getMainDirectory();
	system("cd updates && start woUpdate.exe"); //Check for updates
	setTemporarySprites();

	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Where's Wally?", sf::Style::Close | sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	while (window.isOpen()) {
		window.clear();
		if (checkingForUpdates)
			clientUpdate(&window);	
		else {
			if (MenuActive && !InGameActive) 
				GameMenu(&window);

			else if (InGameActive && !MenuActive) 
				InGame(&window);
		}
		gameEvents(&window);
		window.display();

	}

	return EXIT_SUCCESS;
}