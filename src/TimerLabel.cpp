#include "TimerLabel.hpp"

TimerLabel::TimerLabel(std::string textContent,float textPosX, float textPosY, unsigned int charSize, sf::Color color) {
	font.loadFromFile("Assets/Fonts/Crossten-ExtraBold.ttf");
	text.setFont(font);
	text.setString(textContent);
	text.setFillColor(color);
	text.setPosition(textPosX, textPosY);
	text.setCharacterSize(charSize);

}