#include "GameMenu.hpp"

void GAMEMENU::eliminateNewGame(){
    Json::Value data = getDataJson();
    data["app-properties"]["newgame"] = false;
    std::ofstream fileDataJson("Data/data.json");
    Json::StyledWriter styledwriter;
    fileDataJson << styledwriter.write(data);
    fileDataJson.close();
}


float GAMEMENU::getScaleExitIcon() { return scaleExitIcon; }

void GAMEMENU::loadResources(){
	/* SCALES */
	float screenHeightTemp = sf::VideoMode::getDesktopMode().height;
	scaleExitIcon = /*0.14f;*/ (screenHeightTemp / maxResolution) * 0.1969f;

	/* MENU PAGE */
	createSprite(menuPageTexture, menuPageSprite, "Assets/004/004-mui");
	menuPageSprite.setScale(sf::Vector2f(getFullScreenSpriteScale(), getFullScreenSpriteScale()));
	
	/* EXIT ICON */
	createSprite(exitIconTexture, exitIconSprite, "Assets/002/002-ex");
	exitIconSprite.setScale(sf::Vector2f(getScaleExitIcon(), getScaleExitIcon()));
	exitWidth = (exitIconSprite.getTexture()->getSize().x) * getScaleExitIcon();
	exitHeight = (exitIconSprite.getTexture()->getSize().y) * getScaleExitIcon();
	exitIconSprite.setOrigin(exitIconSprite.getTexture()->getSize().x, 0);
	rangeExitX[0] = (sf::VideoMode::getDesktopMode().width) - exitWidth;
	rangeExitX[1] = sf::VideoMode::getDesktopMode().width;
	rangeExitY[0] = 0;
	rangeExitY[1] = exitHeight;
	exitIconSprite.setPosition(sf::VideoMode::getDesktopMode().width, 0);

	/* NEW GAME INTRO */
	createSprite(openingTexture, openingSprite, "Assets/004/004-opg");
	openingSprite.setScale(sf::Vector2f(getFullScreenSpriteScale(), getFullScreenSpriteScale()));

	/* MENU MUSIC */
	menuMusic.openFromFile("Assets/Audio/music/MenuMusic.wav");
	increaseBar(BARUI::barload);
	currentMusic = &menuMusic;
	
	/* START BUTTON */
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

	unsigned short r = 30, g = 144, b = 255, a = 1020; //RGBA
	sf::Color colorshadesButton(r, g, b, a);
	startButton = new ButtonLabel(sButtonWidth, sButtonHeight, sButtonPosX, sButtonPosY ,sf::Color::Red, sButtonTextPosX, sButtonTextPosY, sButtonTextSize, "START");
	startButtonBorder = new ButtonLabel(sButtonWidthB, sButtonHeightB, sButtonPosBX, sButtonPosBY, colorshadesButton, sButtonTextPosBX, sButtonTextPosBY, 0, "");
	startButtonShadow = new ButtonLabel(sButtonWidthS, sButtonHeightS, sButtonPosSX, sButtonPosSY, sf::Color::Black, sButtonTextPosSX, sButtonTextPosSY, 0, "");

}

void GAMEMENU::notInStateProcess() {}

GAMEMENU::GAMEMENU()
	:State(), openingWriter("", 0.02, 360.0f, 305.0f, 25){
	loadResources();
}

void GAMEMENU::run(sf::RenderWindow *window, const float &dtArg) {
	if (menuMusic.getStatus() != sf::Music::Playing) {
		menuMusic.play();
		menuMusic.setLoop(true);
	}
	window->setMouseCursorVisible(false);

	if (!stateOpening){
		// window->draw(MenuLogoObj->sprite);
		window->draw(menuPageSprite);
		window->draw(*startButtonShadow->getButton());
		window->draw(*startButtonBorder->getButton());
		window->draw(*startButton->getButton());
		window->draw(*startButton->getText());

		window->draw(exitIconSprite);

		if (appInFocus(window)){
			menuMousePos = sf::Mouse::getPosition(*window);
			if ((menuMousePos.x >= startButton->clickableX[0] && menuMousePos.x <= startButton->clickableX[1]) &&
				(menuMousePos.y >= startButton->clickableY[0] && menuMousePos.y <= startButton->clickableY[1])) {
				handSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
				window->draw(handSprite);
			}
			else if ((menuMousePos.x >= rangeExitX[0] && menuMousePos.x <= rangeExitX[1]) &&
				(menuMousePos.y >= rangeExitY[0] && menuMousePos.y <= rangeExitY[1])) {
				handSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
				window->draw(handSprite);
				}
			else {
				arrowSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
				window->draw(arrowSprite);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (!mouseDown){
					if ((menuMousePos.x >= startButton->clickableX[0] && menuMousePos.x <= startButton->clickableX[1]) &&
						(menuMousePos.y >= startButton->clickableY[0] && menuMousePos.y <= startButton->clickableY[1])) {
						globalClickSound.play();
						if (getDataJson()["app-properties"]["newgame"].asBool() == true){
							stateOpening = true;
							openingWriter.tcSetString(openingDialogues[currentDialogueIndex]);
						} else {
							switchingState = "MapSelect";
						}
					}
					else if ((menuMousePos.x >= rangeExitX[0] && menuMousePos.x <= rangeExitX[1]) &&
							(menuMousePos.y >= rangeExitY[0] && menuMousePos.y <= rangeExitY[1])) {
						// if (MessageBoxA(NULL,"Are you sure you want to exit?", "Waldo", MB_YESNO) == IDYES)
								window->close();					
					}
					mouseDown = true;
				}
			} else
				mouseDown = false;
		}
	} else {
		window->draw(openingSprite);
		openingWriter.drawTypeWriter(window);
		openingWriter.updateText(dtArg);
		if(appInFocus(window)){
			menuMousePos = sf::Mouse::getPosition(*window);
			arrowSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
			window->draw(arrowSprite);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && openingWriter.typeWriterStr.length() >= openingWriter.textContent.length()){
				if (!mouseDown){
					globalClickSound.play();
					if (currentDialogueIndex < openingDialogues.size() - 1){
						currentDialogueIndex += 1;
						openingWriter.resetTypeWriter();
						openingWriter.tcSetString(openingDialogues[currentDialogueIndex]);
					} else {
						stateOpening = false;
						currentDialogueIndex = 0;
						openingWriter.resetTypeWriter();
						openingWriter.tcSetString(openingDialogues[currentDialogueIndex]);
						eliminateNewGame();
						switchingState = "MapSelect";
					}
					mouseDown = true;
				}
			} else mouseDown = false;
		}
	}
}