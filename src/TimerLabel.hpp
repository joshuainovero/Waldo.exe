#pragma once
#include <SFML/Graphics.hpp>

class TimerLabel {
private:
	sf::Text text;
	sf::Font font;

public:
	sf::Text *returnText() { return &text; }
	TimerLabel(std::string textContent, float textPosX, float textPosY, unsigned int charSize, sf::Color);
	void moveText(int x, int y) { text.move(x, y); }
};