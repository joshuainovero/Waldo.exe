#pragma once

//std::string textContent, float textPosX, float textPosY, unsigned int charSize
//std::string textContent, float textPosX, float textPosY, unsigned int charSize, sf::Color
TextLabel timerDisplaySeconds("-", sf::VideoMode::getDesktopMode().width / 2, 40.0, 65, sf::Color::White);
TextLabel timerDisplayColon(":", (sf::VideoMode::getDesktopMode().width / 2) - 20, 40.0, 65, sf::Color::White);
TextLabel timerDisplayMinutes("-", (sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 35, 40.0, 65, sf::Color::White);

//Shadow Properties
TextLabel timerShadowSeconds("-", (sf::VideoMode::getDesktopMode().width / 2) + 5, 45.0, 66, sf::Color::Black);
TextLabel timerShadowColon(":", (sf::VideoMode::getDesktopMode().width / 2) - 15, 45.0, 66, sf::Color::Black);
TextLabel timerShadowMinutes("-", ((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 35) + 5, 45.0, 66, sf::Color::Black);

static bool movedText = false; //Prevents the loop to not keep moving
static bool waitRunning = false;
static bool ScreamOn = false;
static bool EnableClick = false;
static bool isOver = false;
static bool wallyFound = false;
static bool textMoved = false;

sf::Clock* wait;
sf::Vector2i inGameMousePos;
const int startingTime = 60;
int countdown = 0;
int tempSeconds = 0;

void resetMapState() {
	//Reset inGame properties
	movedText = false; //Prevents the loop to not keep moving
	waitRunning = false;
	EnableClick = false;
	countdown = 0;
	tempSeconds = 0;
	isOver = false;
	ScreamOn = false;
	wallyFound = false;
	delete wait;
}

void InGame(sf::RenderWindow *inGameWindow) {
	//Responsive Timer -> Start
	if (CurrentMap->clockRunning) {
		if (countdown == 59 && CurrentMap->getMapMinutes() == -1) {
			countdown++;
			CurrentMap->clockRunning = false;
			isOver = true;
			delete CurrentMap->clockTimer;
		}
		if (CurrentMap->getMapMinutes() > 1 && !textMoved) {
			textMoved = true;
			timerDisplayMinutes.returnText()->setPosition((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 27, 40.0);
			timerShadowMinutes.returnText()->setPosition(((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 27) + 5, 45.0);
		}
		//Move Text -> Start
		else if (CurrentMap->getMapMinutes() <= 1 && textMoved) {
			textMoved = false;
			timerDisplayMinutes.returnText()->setPosition((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 35, 40.0);
			timerShadowMinutes.returnText()->setPosition(((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 35) + 5, 45.0);
		}
		if (CurrentMap->getMapMinutes() != 0 && !isOver) {
			timerDisplayMinutes.returnText()->setString(std::to_string(CurrentMap->getMapMinutes()));
			timerShadowMinutes.returnText()->setString(std::to_string(CurrentMap->getMapMinutes()));
		}
		//Move Text -> End

		//Update Countdown -> Start
		sf::Time elapsed = CurrentMap->clockTimer->getElapsedTime();
		if (static_cast<int>(elapsed.asSeconds()) != tempSeconds) {
			tempSeconds = static_cast<int>(elapsed.asSeconds());
			countdown = startingTime - tempSeconds;
			if (countdown == 59) {
				CurrentMap->decrementtMapMinutes();
			}
			if (CurrentMap->getMapMinutes() == 0) {
				//CurrentMap->decrementtMapMinutes();
				timerDisplayMinutes.returnText()->setString("");
				timerShadowMinutes.returnText()->setString("");
			}
		}
		//Update Countdown -> End

		if (countdown >= 10) {
			if (countdown == 60 || (countdown == 59 && CurrentMap->getMapMinutes() == -1)) {
				timerDisplaySeconds.returnText()->setString("00");
				timerShadowSeconds.returnText()->setString("00");
			}
			else {
				timerDisplaySeconds.returnText()->setString(std::to_string(countdown));
				timerShadowSeconds.returnText()->setString(std::to_string(countdown));
			}
		}
		else {
			if (countdown == 0 && CurrentMap->getMapMinutes() != 1)
				CurrentMap->clockTimer->restart();

			else if (countdown >= 0 && countdown != 60){
				timerDisplaySeconds.returnText()->setString("0" + std::to_string(countdown));
				timerShadowSeconds.returnText()->setString("0" + std::to_string(countdown));
			}
					

		}


	}
	//Responsive Timer -> End

	inGameWindow->setMouseCursorVisible(false);
	
	
	if (appInFocus(inGameWindow)){
		inGameMousePos = sf::Mouse::getPosition(*inGameWindow);
		circleCursor.circleSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));

		if (EnableClick) { //Delays
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // If wally is found
				if ((inGameMousePos.x >= CurrentMap->getWallyx1() && inGameMousePos.x <= CurrentMap->getWallyx2()) &&
					(inGameMousePos.y >= CurrentMap->getWallyy1() && inGameMousePos.y <= CurrentMap->getWallyy2())) {
					WallyFound.sound.play();
					wallyFound = true;
					if (CurrentMap->clockRunning) {
						CurrentMap->clockRunning = false;
						delete CurrentMap->clockTimer;
					}
				}
				else WrongClick.sound.play();
			}
		}
	}

	if (static_cast<int>(CurrentMap->clockTimer->getElapsedTime().asSeconds()) == 1) EnableClick = true; //Delay for clicking
	inGameWindow->draw(CurrentMap->returnSprite());
	inGameWindow->draw(circleCursor.circleSprite);

	//Shadow Timer
	inGameWindow->draw(*timerShadowSeconds.returnText());
	inGameWindow->draw(*timerShadowColon.returnText());
	inGameWindow->draw(*timerShadowMinutes.returnText());


	//Actual Timer
	inGameWindow->draw(*timerDisplaySeconds.returnText());
	inGameWindow->draw(*timerDisplayColon.returnText());
	inGameWindow->draw(*timerDisplayMinutes.returnText());
	//inGameWindow->draw(*timerBG.getButton());

	if (isOver) { //Gameover
		//inGameWindow->draw(Jumpscare1.sprite);
		//if (!ScreamOn) {
		//	Scream.sound.play();
		//	ScreamOn = true;
		//}
		CurrentMap->resetMapMinutes();
		if (!waitRunning) {
			wait = new sf::Clock;
			waitRunning = true;
		}
		else {
			sf::Time waitElapse = wait->getElapsedTime();
			if (static_cast<int>(waitElapse.asSeconds()) == 10) {
				resetMapState();
				MenuActive = true;
				InGameActive = false;
			}
		}
	}
	if (wallyFound) {
		resetMapState();
		updateCurrentMapOrder();
		SetMapProperty();
	}


}