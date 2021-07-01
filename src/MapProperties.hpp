#pragma once

#include <string>
#include <unordered_map>
#include <array>
#include <utility>
#include "GameTimer.hpp"
#include "EDassets.hpp"

class MapProperty {	
friend struct WALDOPOSINITIALIZER;
private:
	std::array<int16_t, 4> waldoPosition; //Range of coordinates of wally
	sf::Texture texture;
	sf::Sprite sprite;
	std::string mapOrder;
	static sf::Vector2f currResol;

public:
	GameTimer gametimer;
	bool waldoFound = false;
	bool gameOver = false;
	MapProperty(const std::string &fileName, const std::string &key, const int mapTimerCounts[2]);
	bool checkMouseClick(const sf::Vector2i &inGameMousePosP);
	void resetMapState();
	sf::Sprite returnSprite() { return sprite; }

	~MapProperty() {}
};

