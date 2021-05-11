#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <direct.h>
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

static bool checkingForUpdates = true;

//int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow)
int main() {
	//std::cout << "Debug Console" << std::endl;
	getMainDirectory();
	system("cd updates && start woUpdate.exe");

	//Set temporary sprites for updates
	sf::Texture *textureCheckUpdating = new sf::Texture;
	sf::Sprite *spriteCheckUpdating = new sf::Sprite;
	textureCheckUpdating->loadFromFile("Assets/Maps/CheckUpdates.png");
	spriteCheckUpdating->setTexture(*textureCheckUpdating);
	spriteCheckUpdating->setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));

	sf::Texture *textureCheckUpdatingNow = new sf::Texture;
	sf::Sprite *spriteCheckUpdatingNow = new sf::Sprite;
	textureCheckUpdatingNow->loadFromFile("Assets/Maps/GameUpdating.png");
	spriteCheckUpdatingNow->setTexture(*textureCheckUpdatingNow);
	spriteCheckUpdatingNow->setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));

	sf::Texture *tempArrowCursorTexture = new sf::Texture;
	sf::Sprite  *tempArrowCursorSprite = new sf::Sprite;
	tempArrowCursorTexture->loadFromFile("Assets/Cursors/ArrowCursor.png");
	tempArrowCursorSprite->setTexture(*tempArrowCursorTexture);
	tempArrowCursorSprite->setScale(sf::Vector2f(scaleresol.getScaleArrow(), scaleresol.getScaleArrow()));
	tempArrowCursorSprite->setOrigin(68, 23);

	sf::Vector2i *tempMenuMousePos = new sf::Vector2i;


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
		if (checkingForUpdates){
			window.setMouseCursorVisible(false);
			*tempMenuMousePos = sf::Mouse::getPosition(window);
			tempArrowCursorSprite->setPosition(static_cast<float>(tempMenuMousePos->x), static_cast<float>(tempMenuMousePos->y));
			std::ifstream readUpdateRequired("updates/UpdateRequired");
				std::string checkUpdate;
				readUpdateRequired >> checkUpdate;
				if (checkUpdate != "True"){
					window.draw(*spriteCheckUpdating);
					window.draw(*tempArrowCursorSprite);
				}

				if (checkUpdate == "True"){
					window.draw(*spriteCheckUpdatingNow);
					window.draw(*tempArrowCursorSprite);
					std::ifstream readState("updates/state");
						std::string updateStatus;
						readState >> updateStatus;
					readState.close();
					if (updateStatus == "Updated"){
						updateVersion();
						std::ofstream writeUpdateRequired("updates/UpdateRequired");
							writeUpdateRequired << "ND";
						writeUpdateRequired.close();
						std::ofstream writeState("updates/state");
							writeState << "None";
						writeState.close();
						checkingForUpdates = false;
						delete spriteCheckUpdating;
						delete spriteCheckUpdatingNow;
						delete tempArrowCursorSprite;
						delete textureCheckUpdating;
						delete textureCheckUpdatingNow;
						delete tempArrowCursorTexture;
					}

				}
				else if (checkUpdate == "False"){
					checkingForUpdates = false;
					std::ofstream writeUpdateRequired("updates/UpdateRequired");
						writeUpdateRequired << "ND";
					writeUpdateRequired.close();

					delete spriteCheckUpdating;
					delete spriteCheckUpdatingNow;
					delete tempArrowCursorSprite;
					delete textureCheckUpdating;
					delete textureCheckUpdatingNow;
					delete tempArrowCursorTexture;
				}
				
		}
		else {
			if (MenuActive && !InGameActive) {
				GameMenu(&window);
			}

			else if (InGameActive && !MenuActive) {
				InGame(&window);
			}
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