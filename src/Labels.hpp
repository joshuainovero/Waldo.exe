#pragma once
#include <SFML/Graphics.hpp>

class ButtonLabel {
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Font font;
	
public:
	int clickableX[2], clickableY[2];
	sf::RectangleShape *getButton() { return &button; }
	sf::Text *getText() { return &text; }
	ButtonLabel(float width, float height, float buttonPosX, float buttonPosY, sf::Color, float textPosX, float textPosY, unsigned int charSize, std::string textContent);
};
