#include "WaldoPositions.hpp"
#include "MapProperties.hpp"
#include <Windows.h>
#include <fstream>
#include <iostream>

MapProperty::MapProperty(const std::string &fileName, const std::string &key, const std::array<int, 2> &&mapTimerCounts)
	: gametimer(mapTimerCounts) {
	try{
	std::ifstream checkFile(fileName);
		if (!checkFile.good())
			throw fileName;
		EDassets::decryptFile(fileName);
		increaseBar(BARUI::barload);
		texture.loadFromFile("Assets/sprite.png");
		sprite.setTexture(texture);
		increaseBar(BARUI::barload);
		mapOrder = key;
		const float mapScale = float(sf::VideoMode::getDesktopMode().height / 1080.0f);
		sprite.setScale(sf::Vector2f(mapScale, mapScale));
		for (size_t i = 0; i < waldopositions.MapResol[key].size(); ++i)
			waldoPosition[i] = waldopositions.MapResol[key][i];
	} catch (const std::string &threwFileName){
		if (MessageBoxA(NULL,"An asset has been corrupted or deleted. Please reinstall", "Waldo", MB_ICONERROR) == IDOK){
			std::ofstream emptySpriteFile("Assets/sprite.png", std::ios::binary);
			abort();
		}
	}
}

bool MapProperty::checkMouseClick(const sf::Vector2i &inGameMousePosP) {
	return  ((inGameMousePosP.x >= waldoPosition[0] && inGameMousePosP.x <= waldoPosition[1]) &&
			(inGameMousePosP.y >= waldoPosition[2] && inGameMousePosP.y <= waldoPosition[3]));
}

void MapProperty::resetMapState(){
	if (mapOrder == "Map1"){
		gametimer.seconds = gametimer.m1TimeCounts[0];
		gametimer.minutes = gametimer.m1TimeCounts[1];
	} else if (mapOrder == "Map2"){
		gametimer.seconds = gametimer.m2TimeCounts[0];
		gametimer.minutes = gametimer.m2TimeCounts[1];
	} else if (mapOrder == "Map3"){
		gametimer.seconds = gametimer.m3TimeCounts[0];
		gametimer.minutes = gametimer.m3TimeCounts[1];
	} else if (mapOrder == "Map4"){
		gametimer.seconds = gametimer.m4TimeCounts[0];
		gametimer.minutes = gametimer.m4TimeCounts[1];
	} else if (mapOrder == "Map5"){
		gametimer.seconds = gametimer.m5TimeCounts[0];
		gametimer.minutes = gametimer.m5TimeCounts[1];
	} else if (mapOrder == "Map6"){
		gametimer.seconds = gametimer.m6TimeCounts[0];
		gametimer.minutes = gametimer.m6TimeCounts[1];
	}
	gametimer.stopTimer();
	gameOver = false;
	waldoFound = false;
}
