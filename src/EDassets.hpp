#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>

struct EDassets{
    static constexpr uint32_t key = 1234;
    static void encryptFile(const std::string &nPath);
    static void decryptFile(const std::string &nPath);
};


struct BARUI {
	static sf::RectangleShape barload; 
	static sf::RectangleShape barlimit;
	static void SETPOSITION(const sf::RenderWindow &window);
};
void increaseBar(sf::RectangleShape &bar);
