#pragma once

sf::Vector2i inGameMousePos;
static bool readyForClick = false;

void InGame(sf::RenderWindow *inGameWindow) {
	CircleCursorObj.AnimationCircle.Update(CircleCursorObj.AnimationCircle.currentRow, deltaTime);
	CircleCursorObj.sprite.setTextureRect(CircleCursorObj.AnimationCircle.uvRect);

	if (delayInGameClick >= CurrentMap->gametimer.seconds)
		readyForClick = true;

	inGameWindow->setMouseCursorVisible(false);
	
	if (appInFocus(inGameWindow)){
		inGameMousePos = sf::Mouse::getPosition(*inGameWindow);
		CircleCursorObj.sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
		if (readyForClick){
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // If wally is found
				if (CurrentMap->checkMouseClick(inGameMousePos)) {
						WallyFoundEffect.sound.play();
						CurrentMap->waldoFound = true;
						if (GameClockStruct::ClockRunning) {
							GameClockStruct::ClockRunning = false;
							//delete CurrentMap->clockTimer;
						}
					}
					else WrongClickEffect.sound.play();
				}
		}
		
	}
	if (CurrentMap->gametimer.seconds == -1 && CurrentMap->gametimer.minutes == 0){
		CurrentMap->gametimer.stopTimer();
		CurrentMap->gameOver = true;
	}
	
	if (GameClockStruct::ClockRunning)
		CurrentMap->gametimer.UpdateTimer();

	inGameWindow->draw(CurrentMap->returnSprite());
	inGameWindow->draw(CircleCursorObj.sprite);
	CurrentMap->gametimer.drawTimer(inGameWindow);


	if (CurrentMap->gameOver) {
		CurrentMap->resetMapState();
		TimerLabel::moveTextMinutes = false;
		MenuActive = true;
		InGameActive = false;
		readyForClick = false;

	}

	if (CurrentMap->waldoFound) {
		GameClockStruct::gameClockTimer.restart();
		TimerLabel::moveTextMinutes = false;
		readyForClick = false;
		CurrentMap->resetMapState();
		updateCurrentMapOrder();
		SetMapProperty();
	}


}