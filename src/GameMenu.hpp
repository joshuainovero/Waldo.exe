#pragma once

class GAMEMENU : public State {
private:
	sf::Texture menuPageTexture, exitIconTexture, openingTexture;
	sf::Sprite menuPageSprite, exitIconSprite, openingSprite;
	sf::Music menuMusic;
	ButtonLabel* startButton;
	ButtonLabel* startButtonBorder;
	ButtonLabel* startButtonShadow;
	TypeWriter openingWriter;
	float scaleExitIcon;

	int rangeExitX[2], rangeExitY[2];
	float exitWidth, exitHeight;

	bool stateOpening = false;
	size_t currentDialogueIndex = 0;
	sf::Vector2i menuMousePos;

	const std::array<std::string, 3> openingDialogues{
		"Hello there, gamer! My name is Waldo, and I'm from\nthe Land of Waldos, a land populated by Waldos just\nlike me. You've probably come across me in one of your\nbooks where I'm hidden in various pages",
		"You had a hard time finding me before, didn't you?\nAnyways, I am always ready for an adventure with my\nwalking stick in hand, and my trusty dog Woof by my\nside. I've gotten a little more sophisticated, and I'm\nnow lurking and hidden behind your computer screen.",
		"The rule is straightforward gamer. All you have to do is\nto find me on each map of the game. Simple isn't it? Be\nsure to find me before the clock runs out or else there\nwill be consequences. Best of luck gamer!"
	};

public:
	GAMEMENU();
	void stopMenuMusic() {menuMusic.stop();}
	float getScaleExitIcon();
	virtual void run(sf::RenderWindow *window, const float &dtArg) override;
	virtual void loadResources() override;
};

float GAMEMENU::getScaleExitIcon() { return scaleExitIcon; }

void GAMEMENU::loadResources(){
	/* SCALES */
	float screenHeightTemp = sf::VideoMode::getDesktopMode().height;
	scaleExitIcon = /*0.14f;*/ (screenHeightTemp / maxResolution) * 0.1969f;
	State::fullScreenSpriteScale = /*0.714f;*/ screenHeightTemp / maxResolution;
	State::scaleArrow = /* 0.30f; */ (screenHeightTemp / maxResolution) * 0.42f;

	/* GLOBAL RESOURCES */
	// Arrow cursor
	createSprite(State::arrowTexture, State::arrowSprite, "Assets/001/001-ac");
	State::arrowSprite.setScale(sf::Vector2f(getScaleArrow(), getScaleArrow()));
	State::arrowSprite.setOrigin(68, 23);

	// Hand cursor
	createSprite(State::handTexture, State::handSprite, "Assets/001/001-hc");
	State::handSprite.setScale(sf::Vector2f(getScaleArrow(), getScaleArrow()));
	State::handSprite.setOrigin(110, 30);

	// Global click sound effect
	globalClickBuffer.loadFromFile("Assets/Audio/SoundEffects/MenuSelection.wav");
	globalClickSound.setBuffer(globalClickBuffer);
	increaseBar(BARUI::barload);

	/* MENU PAGE */
	createSprite(menuPageTexture, menuPageSprite, "Assets/004/004-mui");
	menuPageSprite.setScale(sf::Vector2f(State::getFullScreenSpriteScale(), State::getFullScreenSpriteScale()));
	
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
	openingSprite.setScale(sf::Vector2f(State::getFullScreenSpriteScale(), State::getFullScreenSpriteScale()));

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

GAMEMENU::GAMEMENU()
	:openingWriter("", 0.02, 360.0f, 305.0f, 25){
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


		if (Engine::appInFocus(window)){
			menuMousePos = sf::Mouse::getPosition(*window);
			if ((menuMousePos.x >= startButton->clickableX[0] && menuMousePos.x <= startButton->clickableX[1]) &&
				(menuMousePos.y >= startButton->clickableY[0] && menuMousePos.y <= startButton->clickableY[1])) {
				State::handSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
				window->draw(State::handSprite);
			}
			else if ((menuMousePos.x >= rangeExitX[0] && menuMousePos.x <= rangeExitX[1]) &&
				(menuMousePos.y >= rangeExitY[0] && menuMousePos.y <= rangeExitY[1])) {
				State::handSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
				window->draw(State::handSprite);
				}
			else {
				State::arrowSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
				window->draw(State::arrowSprite);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (!Engine::mouseDown){
					if ((menuMousePos.x >= startButton->clickableX[0] && menuMousePos.x <= startButton->clickableX[1]) &&
						(menuMousePos.y >= startButton->clickableY[0] && menuMousePos.y <= startButton->clickableY[1])) {
						globalClickSound.play();
						if (getDataJson()["app-properties"]["newgame"].asBool() == true){
							stateOpening = true;
							openingWriter.tcSetString(openingDialogues[currentDialogueIndex]);
						} else {
							currentState = states.at(1);
						}
					}
					else if ((menuMousePos.x >= rangeExitX[0] && menuMousePos.x <= rangeExitX[1]) &&
							(menuMousePos.y >= rangeExitY[0] && menuMousePos.y <= rangeExitY[1])) {
							globalClickSound.play();
							window->setMouseCursorVisible(true);
						if (MessageBoxA(NULL,"Are you sure you want to exit?", "Waldo", MB_YESNO) == IDYES)
								window->close();					
					}
					Engine::mouseDown = true;
				}
			} else
				Engine::mouseDown = false;
		}
	} else {
		window->draw(openingSprite);
		openingWriter.drawTypeWriter(window);
		openingWriter.updateText(dtArg);
		if(Engine::appInFocus(window)){
			menuMousePos = sf::Mouse::getPosition(*window);
			State::arrowSprite.setPosition(static_cast<float>(menuMousePos.x), static_cast<float>(menuMousePos.y));
			window->draw(State::arrowSprite);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && openingWriter.typeWriterStr.length() >= openingWriter.textContent.length()){
				if (!Engine::mouseDown){
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
						currentState = states.at(1);
					}
					Engine::mouseDown = true;
				}
			} else Engine::mouseDown = false;
		}
	}
}