#pragma once
#include <SFML\Graphics.hpp>
#include "GameTimer.hpp"

class MapProperty 
{	
private:
	std::array<int16_t, 4> waldoPosition; //Range of coordinates of wally
	sf::Texture texture;
	sf::Sprite sprite;
	std::string mapOrder;

public:
	GameTimer gametimer;
	uint32_t responsiveResolutionMap;
	bool checkMouseClick(const sf::Vector2i &inGameMousePosP);
	void resetMapState();
	bool waldoFound = false;
	bool gameOver = false;
	MapProperty(std::string fileName, std::string key, const int mapTimerCounts[2]);
	sf::Sprite returnSprite() { return sprite; }

	~MapProperty() {}
};

