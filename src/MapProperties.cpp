#include <string>
#include <SFML/Graphics.hpp>
#include "MapProperties.hpp"
#include <iostream>
#include <array>
#include <utility>
#include <unordered_map>

namespace WaldoPositions
{

	namespace Resol720p
	{
		std::unordered_map<std::string, std::array<int16_t, 4>> MapResol;
		struct initWaldoPosition720p {
			initWaldoPosition720p(){
				MapResol["Map1"] = { 982, 1032, 373, 428 };
				MapResol["Map2"] = { 818, 868, 281, 329 };
				MapResol["Map3"] = { 121, 161, 688, 714 };
				MapResol["Map4"] = { 1200, 1238, 558, 591 };
				MapResol["Map5"] = { 1151, 1182, 615, 650 };
				MapResol["Map6"] = { 842, 873, 531, 551 };
			}
		};
		initWaldoPosition720p declare;
	}

	namespace Resol1080p
	{
		std::unordered_map<std::string, std::array<int16_t, 4>> MapResol;
		struct initWaldoPosition1080p {
			initWaldoPosition1080p(){
				MapResol["Map1"] = { 1386, 1432, 537, 687 };
				MapResol["Map2"] = { 1159, 1200, 408, 447 };
				MapResol["Map3"] = { 177, 215, 965, 1003 };
				MapResol["Map4"] = { 1685, 1728, 793, 828 };
				MapResol["Map5"] = { 1615, 1653, 869, 909 };
				MapResol["Map6"] =  { 1176, 1217, 745, 775 };
			}
		};
	initWaldoPosition1080p declare;
	}


}

MapProperty::MapProperty(std::string fileName, std::string key, const int mapTimerCounts[2])
	: gametimer(mapTimerCounts) {
	responsiveResolutionMap = sf::VideoMode::getDesktopMode().height;
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
	mapOrder = key;
	const float mapScale = float(sf::VideoMode::getDesktopMode().height / 1080.0f);
	sprite.setScale(sf::Vector2f(mapScale, mapScale));

	if (responsiveResolutionMap <= 768){
		for (size_t i = 0; i < WaldoPositions::Resol720p::MapResol[key].size(); ++i)
			waldoPosition[i] = WaldoPositions::Resol720p::MapResol[key][i];
	}
	else if (responsiveResolutionMap >= 1080){
		for (size_t i = 0; i < WaldoPositions::Resol1080p::MapResol[key].size(); ++i)
			waldoPosition[i] = WaldoPositions::Resol1080p::MapResol[key][i];

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
