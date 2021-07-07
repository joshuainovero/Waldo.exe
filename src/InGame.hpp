#pragma once

class INGAME : public State{
private:
	sf::Vector2i inGameMousePos;
	bool gamePause = false;
	bool keyDown = false;
public:
	INGAME() = default;
	virtual void run(sf::RenderWindow *window, const float &dtArg) override;
};

void INGAME::run(sf::RenderWindow *window, const float &dtArg) {
	window->setMouseCursorVisible(false);
	if (gamePause) {
		inGameMousePos = sf::Mouse::getPosition(*window);
		window->draw(PauseScreenObj->sprite);

		if (PauseScreenObj->resumeInRange(inGameMousePos)){
			HandCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			window->draw(HandCursorObj->sprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if (!Engine::mouseDown){
					MenuSelectionEffect->sound.play();
					gamePause = false;
					Engine::mouseDown = true;
				}
			} else
				Engine::mouseDown = false;
		}
		else if (PauseScreenObj->quitInRange(inGameMousePos)){
			HandCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			window->draw(HandCursorObj->sprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				MenuSelectionEffect->sound.play();
				window->setMouseCursorVisible(true);
				if (MessageBoxA(NULL,"Are you sure you want to go to the main menu?", "Waldo", MB_YESNO) == IDYES){
					CurrentMap->gametimer.stopTimer();
					CurrentMap->resetMapState();
					TimerLabel::moveTextMinutes = false;
					gamePause = false;
					currentState = states.at(0);
				}
			}
		} else {
			ArrowCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			window->draw(ArrowCursorObj->sprite);
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
			inGameMousePos = sf::Mouse::getPosition(*window);
			window->draw(CurrentMap->returnSprite());
			CurrentMap->gametimer.drawTimer(window);
			window->draw(WaldoFoundObj->sprite);
			if (WaldoFoundObj->continueInRange(inGameMousePos)){
				HandCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(HandCursorObj->sprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!Engine::mouseDown){
						GameClockStruct::gameClockTimer.restart();
						CurrentMap->resetMapState();
						TimerLabel::moveTextMinutes = false;
						if (currentMapIndex < getDataJson()["gameplay-status"]["currentmaporder"].asInt()){
							currentMapIndex += 1;
							gotoChosenMap(currentMapIndex);
						} else {
							updateCurrentMapOrder();
							currentMapIndex = getDataJson()["gameplay-status"]["currentmaporder"].asInt();
							updateMapStatus();
							SetMapProperty();
						}
						Engine::mouseDown = true;
					}
				} else
					Engine::mouseDown = false;
			} else {
				ArrowCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(ArrowCursorObj->sprite);
			}
		} else if (CurrentMap->gameOver){
			inGameMousePos = sf::Mouse::getPosition(*window);
			window->draw(CurrentMap->returnSprite());
			CurrentMap->gametimer.drawTimer(window);
			window->draw(GameOverObj->sprite);
			if (GameOverObj->continueInRange(inGameMousePos)){
				HandCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(HandCursorObj->sprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!Engine::mouseDown){
						CurrentMap->resetMapState();
						TimerLabel::moveTextMinutes = false;
						Engine::mouseDown = true;
						currentState = states.at(0);
					}
				} else
					Engine::mouseDown = false;
			} else {
				ArrowCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(ArrowCursorObj->sprite);
			}

		} else {
			CircleCursorObj->AnimationCircle.Update(CircleCursorObj->AnimationCircle.currentRow, dtArg);
			CircleCursorObj->sprite.setTextureRect(CircleCursorObj->AnimationCircle.uvRect);
			
			if (appInFocus(window)){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
					if (!keyDown){
						gamePause = true;
						keyDown = true;
					}
				} else {
					keyDown = false;
				}
				inGameMousePos = sf::Mouse::getPosition(*window);
				CircleCursorObj->sprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // If wally is found
					if (!Engine::mouseDown){
						if (CurrentMap->checkMouseClick(inGameMousePos)) {
							WallyFoundEffect->sound.play();
							CurrentMap->waldoFound = true;
							if (GameClockStruct::ClockRunning) {
								GameClockStruct::ClockRunning = false;
							}
						}
						else WrongClickEffect->sound.play();
						Engine::mouseDown = true;
					}
				} else
					Engine::mouseDown = false;		
			}
			if (CurrentMap->gametimer.seconds == -1 && CurrentMap->gametimer.minutes == 0){
				CurrentMap->gametimer.stopTimer();
				CurrentMap->gameOver = true;
			}
			
			if (GameClockStruct::ClockRunning)
				CurrentMap->gametimer.UpdateTimer();

			window->draw(CurrentMap->returnSprite());
			window->draw(CircleCursorObj->sprite);
			CurrentMap->gametimer.drawTimer(window);
		}
	}		
}
