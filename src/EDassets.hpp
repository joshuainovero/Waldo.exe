#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

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
