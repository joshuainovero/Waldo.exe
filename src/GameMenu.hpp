#pragma once

ButtonLabel* startButton;
ButtonLabel* startButtonBorder;
ButtonLabel* startButtonShadow;

struct initMenuButtons {
	int screenResol = sf::VideoMode::getDesktopMode().height;
	const float maxWidth = 1920;
	const float maxHeight = 1080;
	float screenWidth = sf::VideoMode::getDesktopMode().width;
	float screenHeight = sf::VideoMode::getDesktopMode().height;

	// Start Button
	float sButtonWidth = screenWidth * 0.1120058565f;
	float sButtonHeight = screenHeight * 0.06901041667f;
	float sButtonPosX = screenWidth * 0.5168374817f;
	float sButtonPosY = screenHeight * 0.6588541667f;
	float sButtonTextPosX = screenWidth * 0.5285505125f;
	float sButtonTextPosY = screenHeight * 0.6588541667f;
	float sButtonTextSize = screenHeight * 0.05555555556f;

	// Start Button Border
	float sButtonWidthB = screenWidth * 0.1200585652f;
	float sButtonHeightB = screenHeight * 0.08333333333f;
	float sButtonPosBX = screenWidth * 0.5124450952f;
	float sButtonPosBY = screenHeight * 0.6510416667f;
	float sButtonTextPosBX = screenWidth * 0.5270863839f;
	float sButtonTextPosBY = screenHeight * 0.6510416667f;

	// Start Button Shadow
	float sButtonWidthS = screenWidth * 0.1200585652f;
	float sButtonHeightS = screenHeight * 0.08333333333f;
	float sButtonPosSX = screenWidth * 0.5161054173f;
	float sButtonPosSY = screenHeight * 0.6575520833f;
	float sButtonTextPosSX = screenWidth * 0.5270863839f;
	float sButtonTextPosSY = screenHeight * 0.6510416667f;
	initMenuButtons() {
		unsigned short r = 30, g = 144, b = 255, a = 1020; //RGBA
		sf::Color colorshadesButton(r, g, b, a);
		startButton = new ButtonLabel(sButtonWidth, sButtonHeight, sButtonPosX, sButtonPosY ,sf::Color::Red, sButtonTextPosX, sButtonTextPosY, sButtonTextSize, "START");
		startButtonBorder = new ButtonLabel(sButtonWidthB, sButtonHeightB, sButtonPosBX, sButtonPosBY, colorshadesButton, sButtonTextPosBX, sButtonTextPosBY, 0, "");
		startButtonShadow = new ButtonLabel(sButtonWidthS, sButtonHeightS, sButtonPosSX, sButtonPosSY, sf::Color::Black, sButtonTextPosSX, sButtonTextPosSY, 0, "");
	}
};
initMenuButtons initmenubuttons;
sf::Vector2i menuMousePos;
void GameMenu(sf::RenderWindow* menuWindow) {
	if (Intromusic.music.getStatus() != sf::Music::Playing) {
		Intromusic.music.play();
		Intromusic.music.setLoop(true);
	}
	menuWindow->setMouseCursorVisible(false);

	menuWindow->draw(MenuLogoObj.sprite);
	menuWindow->draw(*startButtonShadow->getButton());
	menuWindow->draw(*startButtonBorder->getButton());
	menuWindow->draw(*startButton->getButton());
	menuWindow->draw(*startButton->getText());

	menuWindow->draw(ExitIconObj.sprite);

	if (appInFocus(menuWindow)){
		menuMousePos = sf::Mouse::getPosition(*menuWindow);
		if ((menuMousePos.x >= startButton->clickableX[0] && menuMousePos.x <= startButton->clickableX[1]) &&
			(menuMousePos.y >= startButton->clickableY[0] && menuMousePos.y <= startButton->clickableY[1])) {
			HandCursorObj.sprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
			menuWindow->draw(HandCursorObj.sprite);
		}
		else if ((menuMousePos.x >= ExitIconObj.clickableX[0] && menuMousePos.x <= ExitIconObj.clickableX[1]) &&
			(menuMousePos.y >= ExitIconObj.clickableY[0] && menuMousePos.y <= ExitIconObj.clickableY[1])) {
			HandCursorObj.sprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
			menuWindow->draw(HandCursorObj.sprite);
			}
		else {
			ArrowCursorObj.sprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
			menuWindow->draw(ArrowCursorObj.sprite);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if ((menuMousePos.x >= startButton->clickableX[0] && menuMousePos.x <= startButton->clickableX[1]) &&
				(menuMousePos.y >= startButton->clickableY[0] && menuMousePos.y <= startButton->clickableY[1])) {
				SetMapProperty();
			}
			else if ((menuMousePos.x >= ExitIconObj.clickableX[0] && menuMousePos.x <= ExitIconObj.clickableX[1]) &&
					(menuMousePos.y >= ExitIconObj.clickableY[0] && menuMousePos.y <= ExitIconObj.clickableY[1])) {
					menuWindow->setMouseCursorVisible(true);
				   if (MessageBoxA(NULL,"Are you sure you want to exit?", "Waldo", MB_YESNO) == IDYES)
        				menuWindow->close();					
			}
		}
	}









}