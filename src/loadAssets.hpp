#pragma once
#include <thread>

static bool done = false;
void decryptAssets(){
	State::states.push_back(new GAMEMENU);
	State::states.push_back(new MAPSELECT);
	State::states.push_back(new INGAME);
	INGAME::loadMaps();
	done = true;
}

void loadingScreen(){
	std::unique_ptr<sf::Texture> textureLoading = std::make_unique<sf::Texture>();
	std::unique_ptr<sf::Sprite> spriteLoading = std::make_unique<sf::Sprite>();
	float spriteScale = (sf::VideoMode::getDesktopMode().height * 0.50) / 1080.0f;
	EDassets::decryptFile("Assets/004/004-ld");
	increaseBar(BARUI::barload);
	textureLoading->loadFromFile("Assets/sprite.png");
	spriteLoading->setTexture(*textureLoading);
	increaseBar(BARUI::barload);
	spriteLoading->setScale(spriteScale, spriteScale);
	
	sf::RenderWindow loadWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width * 0.50, sf::VideoMode::getDesktopMode().height * 0.50), "Where's Wally?", sf::Style::None);

	BARUI::SETPOSITION(loadWindow);
	std::thread threadLoadAssets(decryptAssets);
	while (loadWindow.isOpen()){
		sf::Event evnt;
		while (loadWindow.pollEvent(evnt)){
		if (evnt.type == sf::Event::Closed)
			loadWindow.close();
		}
		loadWindow.clear();
		loadWindow.draw(*spriteLoading);
		loadWindow.draw(BARUI::barlimit);
		loadWindow.draw(BARUI::barload);
		loadWindow.display();

		if (done)
			loadWindow.close();
	}
	threadLoadAssets.join();


}