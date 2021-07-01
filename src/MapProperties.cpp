#include "WaldoPositions.hpp"
#include <Windows.h>
#include <fstream>
#include <iostream>

MapProperty::MapProperty(const std::string &fileName, const std::string &key, const int mapTimerCounts[2])
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
		if (MessageBoxA(NULL,"An asset has been corrupted or deleted. Please reinstall", "Waldo", MB_ICONERROR) == IDOK)
			abort();
	}
}

bool MapProperty::checkMouseClick(const sf::Vector2i &inGameMousePosP) {
	return  ((inGameMousePosP.x >= waldoPosition[0] && inGameMousePosP.x <= waldoPosition[1]) &&
			(inGameMousePosP.y >= waldoPosition[2] && inGameMousePosP.y <= waldoPosition[3]));
}

void MapProperty::resetMapState(){
	if (mapOrder == "Map1"){
		gametimer.seconds = GameTimer::m1TimeCounts[0];
		gametimer.minutes = GameTimer::m1TimeCounts[1];
	} else if (mapOrder == "Map2"){
		gametimer.seconds = GameTimer::m2TimeCounts[0];
		gametimer.minutes = GameTimer::m2TimeCounts[1];
	} else if (mapOrder == "Map3"){
		gametimer.seconds = GameTimer::m3TimeCounts[0];
		gametimer.minutes = GameTimer::m3TimeCounts[1];
	} else if (mapOrder == "Map4"){
		gametimer.seconds = GameTimer::m4TimeCounts[0];
		gametimer.minutes = GameTimer::m4TimeCounts[1];
	} else if (mapOrder == "Map5"){
		gametimer.seconds = GameTimer::m5TimeCounts[0];
		gametimer.minutes = GameTimer::m5TimeCounts[1];
	} else if (mapOrder == "Map6"){
		gametimer.seconds = GameTimer::m6TimeCounts[0];
		gametimer.minutes = GameTimer::m6TimeCounts[1];
	}
	gameOver = false;
	waldoFound = false;
}
