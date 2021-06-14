#pragma once

sf::Vector2i inGameMousePos;
static bool gamePause = false;
static bool keyDown = false;

void InGame(sf::RenderWindow *inGameWindow) {
	inGameWindow->setMouseCursorVisible(false);
	if (gamePause) {
		inGameMousePos = sf::Mouse::getPosition(*inGameWindow);
		inGameWindow->draw(PauseScreenObj->sprite);

		if (PauseScreenObj->resumeInRange(inGameMousePos)){
			HandCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			inGameWindow->draw(HandCursorObj->sprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if (!mouseDown){
					gamePause = false;
					mouseDown = true;
				}
			} else
				mouseDown = false;
		}
		else if (PauseScreenObj->quitInRange(inGameMousePos)){
			HandCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			inGameWindow->draw(HandCursorObj->sprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				inGameWindow->setMouseCursorVisible(true);
				if (MessageBoxA(NULL,"Are you sure you want to go to the main menu?", "Waldo", MB_YESNO) == IDYES){
					CurrentMap->gametimer.stopTimer();
				 	CurrentMap->resetMapState();
			 		TimerLabel::moveTextMinutes = false;
			 		MenuActive = true;
			 		InGameActive = false;
					gamePause = false;
				}
			}
		} else {
			ArrowCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			inGameWindow->draw(ArrowCursorObj->sprite);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if (!keyDown){
				gamePause = false;
				keyDown = true;
			}
			
		}  else keyDown = false;
		GameClockStruct::gameClockTimer.restart();
	} else {
		if (CurrentMap->waldoFound){
			inGameMousePos = sf::Mouse::getPosition(*inGameWindow);
			inGameWindow->draw(CurrentMap->returnSprite());
			CurrentMap->gametimer.drawTimer(inGameWindow);
			inGameWindow->draw(WaldoFoundObj->sprite);
			if (WaldoFoundObj->continueInRange(inGameMousePos)){
				HandCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				inGameWindow->draw(HandCursorObj->sprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!mouseDown){
						GameClockStruct::gameClockTimer.restart();
						TimerLabel::moveTextMinutes = false;
						CurrentMap->resetMapState();
						updateCurrentMapOrder();
						SetMapProperty();
						mouseDown = true;
					}
				} else
					mouseDown = false;
			} else {
				ArrowCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				inGameWindow->draw(ArrowCursorObj->sprite);
			}
		} else if (CurrentMap->gameOver){
			inGameMousePos = sf::Mouse::getPosition(*inGameWindow);
			inGameWindow->draw(CurrentMap->returnSprite());
			CurrentMap->gametimer.drawTimer(inGameWindow);
			inGameWindow->draw(GameOverObj->sprite);
			if (GameOverObj->continueInRange(inGameMousePos)){
				HandCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				inGameWindow->draw(HandCursorObj->sprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!mouseDown){
						CurrentMap->resetMapState();
						TimerLabel::moveTextMinutes = false;
						MenuActive = true;
						InGameActive = false;
						mouseDown = true;
					}
				} else
					mouseDown = false;
			} else {
				ArrowCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				inGameWindow->draw(ArrowCursorObj->sprite);
			}

		} else {
			CircleCursorObj->AnimationCircle.Update(CircleCursorObj->AnimationCircle.currentRow, deltaTime);
			CircleCursorObj->sprite.setTextureRect(CircleCursorObj->AnimationCircle.uvRect);
			
			if (appInFocus(inGameWindow)){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
					if (!keyDown){
						gamePause = true;
						keyDown = true;
					}
				} else {
					keyDown = false;
				}
				inGameMousePos = sf::Mouse::getPosition(*inGameWindow);
				CircleCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // If wally is found
					if (!mouseDown){
						if (CurrentMap->checkMouseClick(inGameMousePos)) {
							WallyFoundEffect->sound.play();
							CurrentMap->waldoFound = true;
							if (GameClockStruct::ClockRunning) {
								GameClockStruct::ClockRunning = false;
							}
						}
						else WrongClickEffect->sound.play();
						mouseDown = true;
					}
				} else
					mouseDown = false;		
			}
			if (CurrentMap->gametimer.seconds == -1 && CurrentMap->gametimer.minutes == 0){
				CurrentMap->gametimer.stopTimer();
				CurrentMap->gameOver = true;
			}
			
			if (GameClockStruct::ClockRunning)
				CurrentMap->gametimer.UpdateTimer();

			inGameWindow->draw(CurrentMap->returnSprite());
			inGameWindow->draw(CircleCursorObj->sprite);
			CurrentMap->gametimer.drawTimer(inGameWindow);


			// if (CurrentMap->gameOver) {
			// 	CurrentMap->resetMapState();
			// 	TimerLabel::moveTextMinutes = false;
			// 	MenuActive = true;
			// 	InGameActive = false;

			// }

			// if (CurrentMap->waldoFound) {
			// 	GameClockStruct::gameClockTimer.restart();
			// 	TimerLabel::moveTextMinutes = false;
			// 	CurrentMap->resetMapState();
			// 	updateCurrentMapOrder();
			// 	SetMapProperty();
			// }
		}
	}


}