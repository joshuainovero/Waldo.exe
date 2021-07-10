#include "Labels.hpp"

ButtonLabel::ButtonLabel(float width, float height, float buttonPosX, float buttonPosY, sf::Color color, float textPosX, float textPosY, unsigned int charSize, std::string textContent) {
	button.setSize(sf::Vector2f(width, height));
	button.setPosition(sf::Vector2f(buttonPosX,buttonPosY));
	button.setFillColor(color);
	
	font.loadFromFile("Assets/Fonts/Crossten-ExtraBold.ttf");
	text.setFont(font);
	text.setString(textContent);
	text.setPosition(sf::Vector2f(textPosX, textPosY));
	text.setCharacterSize(charSize);

	//Calculate the clickable area
	clickableX[0] = buttonPosX;
	clickableX[1] = buttonPosX + width;
	clickableY[0] = buttonPosY;
	clickableY[1] = buttonPosY + height;
	
}