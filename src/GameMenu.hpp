#pragma once
//float width, float height, float buttonPosX, float buttonPosY, sf::Color, float textPosX, float textPosY, unsigned int charSize, std::string textContent
//ButtonLabel startButton(153, 53, 706, 506,sf::Color::Red, 722, 506, 40, "START");
//ButtonLabel startButtonBorder(164, 64, 700, 500, sf::Color::Color(30, 144, 255, 1020), 720, 500, 50, "");
//ButtonLabel startButtonShadow(164, 64, 705, 505, sf::Color::Black, 720, 500, 50, "");
ButtonLabel* startButton;
ButtonLabel* startButtonBorder;
ButtonLabel* startButtonShadow;

struct initMenuButtons {
	int screenResol = sf::VideoMode::getDesktopMode().height;
	initMenuButtons() {
		sf::Color colorshadesButton(30, 144, 255, 1020);
		if (screenResol == 1080) {
			startButton = new ButtonLabel(215.0512445f, 74.53125f, 992.3279649f, 711.5625f, sf::Color::Red, 1014.816984, 711.5625, 60, "START");
			startButtonBorder = new ButtonLabel(230.5124451f, 90.0f, 983.8945827f, 703.125f, colorshadesButton, 1012.005857, 703.125, 50, "");
			startButtonShadow = new ButtonLabel(230.5124451f, 90.0f, 990.9224012f, 710.15625f, sf::Color::Black, 1012.005857, 703.125, 50, "");
		}
		else if (screenResol == 768) {	
			startButton = new ButtonLabel(153, 53, 706, 506,sf::Color::Red, 722, 506, 40, "START");
			startButtonBorder = new ButtonLabel(164, 64, 700, 500, colorshadesButton, 720, 500, 50, "");
			startButtonShadow = new ButtonLabel(164, 64, 705, 505, sf::Color::Black, 720, 500, 50, "");
		}
	}
};
initMenuButtons initmenubuttons;

void GameMenu(sf::RenderWindow* menuWindow) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(*menuWindow);
	if (intro.music.getStatus() != sf::Music::Playing) {
		intro.music.play();
		intro.music.setLoop(true);
	}
	menuWindow->setMouseCursorVisible(false);

	//for (auto c : startButton.clickableX) std::cout << c << " "; std::cout << std::endl;
	//for (auto c : startButton.clickableY) std::cout << c << " "; std::cout << std::endl;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if ((mousePos.x >= startButton->clickableX[0] && mousePos.x <= startButton->clickableX[1]) &&
			(mousePos.y >= startButton->clickableY[0] && mousePos.y <= startButton->clickableY[1])) {
			SetMapProperty();
		}
	}


	menuWindow->draw(MenuLogo.spriteMenuLogo);
	menuWindow->draw(*startButtonShadow->getButton());
	menuWindow->draw(*startButtonBorder->getButton());
	menuWindow->draw(*startButton->getButton());
	menuWindow->draw(*startButton->getText());

	if ((mousePos.x >= startButton->clickableX[0] && mousePos.x <= startButton->clickableX[1]) &&
		(mousePos.y >= startButton->clickableY[0] && mousePos.y <= startButton->clickableY[1])) {
		HandCursor.handCursorSprite.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
		menuWindow->draw(HandCursor.handCursorSprite);
	}
	else {
		ArrowCursor.arrowCursorSprite.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
		menuWindow->draw(ArrowCursor.arrowCursorSprite);
	}






}