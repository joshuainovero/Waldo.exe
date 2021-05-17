#pragma once
#include <SFML\Graphics.hpp>

class MapProperty {
protected:
	int wallyPosition[4]; //Range of coordinates of wally
	int mapMinutes = 1;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	bool clockRunning = false;
	sf::Clock* clockTimer;
	uint32_t responsiveResolutionMap;
	MapProperty(std::string fileName);

	void decrementtMapMinutes() { mapMinutes -= 1; }
	void resetMapMinutes() { mapMinutes = 1; }

	sf::Sprite returnSprite() { return sprite; }
	int getWallyx1() { return wallyPosition[0]; }
	int getWallyx2() { return wallyPosition[1]; }
	int getWallyy1() { return wallyPosition[2]; }
	int getWallyy2() { return wallyPosition[3]; }
	int getMapMinutes() { return mapMinutes; }

	~MapProperty() { delete clockTimer;}
};

class Map1 : public MapProperty {
private:
	const int wallyResol768Pos[4] = { 982, 1032, 373, 428 };
	const int wallyResol1080Pos[4] = { 1386, 1432, 537, 687 };
public:
	Map1(std::string fileName);
		
};

class Map2 : public MapProperty {
private:
	const int wallyResol768Pos[4] = { 818, 868, 281, 329 };
	const int wallyResol1080Pos[4] = { 1159, 1200, 408, 447 };
public:
	Map2(std::string fileName);

};

class Map3 : public MapProperty {
private:
	const int wallyResol768Pos[4] = { 121, 161, 688, 714 };
	const int wallyResol1080Pos[4] = { 177, 215, 965, 1003 };
public:
	Map3(std::string fileName);

};

class Map4 : public MapProperty {
private:
	const int wallyResol768Pos[4] = { 1200, 1238, 558, 591 };
	const int wallyResol1080Pos[4] = { 1685, 1728, 793, 828 };
public:
	Map4(std::string fileName);

};

class Map5 : public MapProperty {
private:
	const int wallyResol768Pos[4] = { 1151, 1182, 615, 650 };
	const int wallyResol1080Pos[4] = { 1615, 1653, 869, 909 };
public:
	Map5(std::string fileName);

};

class Map6 : public MapProperty {
private:
	const int wallyResol768Pos[4] = { 842, 873, 531, 551 };
	const int wallyResol1080Pos[4] = { 1176, 1217, 745, 775 };
public:
	Map6(std::string fileName);

};

