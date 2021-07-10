#pragma once

#include <string>
#include <unordered_map>
#include <array>
#include <utility>

#include "GameTimer.hpp"
#include "EDassets.hpp"

class MapProperty {	
private:
	std::array<int16_t, 4> waldoPosition; //Range of coordinates of wally
	sf::Texture texture;
	sf::Sprite sprite;
	std::string mapOrder;

public:
	GameTimer gametimer;
	bool waldoFound = false;
	bool gameOver = false;
	MapProperty(const std::string &fileName, const std::string &key, const std::array<int, 2> &&mapTimerCounts);
	bool checkMouseClick(const sf::Vector2i &inGameMousePosP);
	void resetMapState();
	sf::Sprite returnSprite() { return sprite; }

	~MapProperty() {}
};

