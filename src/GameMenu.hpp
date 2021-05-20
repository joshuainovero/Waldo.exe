#pragma once
//float width, float height, float buttonPosX, float buttonPosY, sf::Color, float textPosX, float textPosY, unsigned int charSize, std::string textContent

ButtonLabel* startButton;
ButtonLabel* startButtonBorder;
ButtonLabel* startButtonShadow;


struct initMenuButtons {
	int screenResol = sf::VideoMode::getDesktopMode().height;
	initMenuButtons() {
		unsigned short r = 30, g = 144, b = 255, a = 1020; //RGBA
		sf::Color colorshadesButton(r, g, b, a);
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
sf::Vector2i menuMousePos;
void GameMenu(sf::RenderWindow* menuWindow) {
	if (intro.music.getStatus() != sf::Music::Playing) {
		intro.music.play();
		intro.music.setLoop(true);
	}
	menuWindow->setMouseCursorVisible(false);

	menuWindow->draw(MenuLogo.spriteMenuLogo);
	menuWindow->draw(*startButtonShadow->getButton());
	menuWindow->draw(*startButtonBorder->getButton());
	menuWindow->draw(*startButton->getButton());
	menuWindow->draw(*startButton->getText());

	menuWindow->draw(ExitIcon.exitIconSprite);

	if (appInFocus(menuWindow)){
		menuMousePos = sf::Mouse::getPosition(*menuWindow);
		if ((menuMousePos.x >= startButton->clickableX[0] && menuMousePos.x <= startButton->clickableX[1]) &&
			(menuMousePos.y >= startButton->clickableY[0] && menuMousePos.y <= startButton->clickableY[1])) {
			HandCursor.handCursorSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
			menuWindow->draw(HandCursor.handCursorSprite);
		}
		else if ((menuMousePos.x >= ExitIcon.clickableX[0] && menuMousePos.x <= ExitIcon.clickableX[1]) &&
			(menuMousePos.y >= ExitIcon.clickableY[0] && menuMousePos.y <= ExitIcon.clickableY[1])) {
			HandCursor.handCursorSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
			menuWindow->draw(HandCursor.handCursorSprite);
			}
		else {
			ArrowCursor.arrowCursorSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
			menuWindow->draw(ArrowCursor.arrowCursorSprite);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if ((menuMousePos.x >= startButton->clickableX[0] && menuMousePos.x <= startButton->clickableX[1]) &&
				(menuMousePos.y >= startButton->clickableY[0] && menuMousePos.y <= startButton->clickableY[1])) {
				SetMapProperty();
			}
			else if ((menuMousePos.x >= ExitIcon.clickableX[0] && menuMousePos.x <= ExitIcon.clickableX[1]) &&
					(menuMousePos.y >= ExitIcon.clickableY[0] && menuMousePos.y <= ExitIcon.clickableY[1])) {
					menuWindow->setMouseCursorVisible(true);
				   if (MessageBoxA(NULL,"Are you sure you want to exit?", "Waldo", MB_YESNO) == IDYES)
        				menuWindow->close();					
			}
		}
	}









}