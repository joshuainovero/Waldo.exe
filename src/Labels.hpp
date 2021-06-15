#pragma once
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



class TextLabel {
private:
	sf::Text text;
	sf::Font font;

public:
	sf::Text *returnText() { return &text; }
	TextLabel(std::string textContent, float textPosX, float textPosY, unsigned int charSize, sf::Color);
	void moveText(int x, int y) { text.move(x, y); }
};
TextLabel::TextLabel(std::string textContent,float textPosX, float textPosY, unsigned int charSize, sf::Color color) {
	font.loadFromFile("Assets/Fonts/Crossten-ExtraBold.ttf");
	text.setFont(font);
	text.setString(textContent);
	text.setFillColor(color);
	text.setPosition(textPosX, textPosY);
	text.setCharacterSize(charSize);

}
