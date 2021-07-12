#include "InGame.hpp"

/* STATES */
//Pause
//!Pause -> Waldo is found or Gameover,  else find Waldo

void INGAME::loadMaps(){
	MAP1 = new MapProperty("Assets/003/003-m1", "Map1", {30,1});
	MAP2 = new MapProperty("Assets/003/003-m2", "Map2", {10,1});
	MAP3 = new MapProperty("Assets/003/003-m3", "Map3", {5,2});
	MAP4 = new MapProperty("Assets/003/003-m4", "Map4", {30,2});
	MAP5 = new MapProperty("Assets/003/003-m5", "Map5", {45,0});
	MAP6 = new MapProperty("Assets/003/003-m6", "Map6", {20,2});
}

void INGAME::SetMapProperty() {
	switch (getDataJson()["gameplay-status"]["currentmaporder"].asInt()) {
		case 0: CurrentMap = MAP1; break;
		case 1: CurrentMap = MAP2; break;
		case 2: CurrentMap = MAP3; break;
		case 3: CurrentMap = MAP4; break;
		case 4: CurrentMap = MAP5; break;
		case 5: CurrentMap = MAP6; break;
	}
	CurrentMap->gametimer.startTimer();
	CurrentMap->gametimer.gameClockTimer->restart();

}

void INGAME::gotoChosenMap(){
	if (gotoMapTriggered){
		currentMapIndex = getDataJson()["gameplay-status"]["gotomap"]["index"].asInt();
	}
	switch (currentMapIndex){
		case 0: CurrentMap = MAP1; break;
		case 1: CurrentMap = MAP2; break;
		case 2: CurrentMap = MAP3; break;
		case 3: CurrentMap = MAP4; break;
		case 4: CurrentMap = MAP5; break;
		case 5: CurrentMap = MAP6; break;
	}
	// Intromusic->music.stop();
	//State::states.at(0)->stopCurrentMusicPlaying();
	// State::currentState = State::states.at(2);
	// CurrentMap->gametimer.ClockRunning = true;
	CurrentMap->gametimer.startTimer();
	CurrentMap->gametimer.gameClockTimer->restart();
}


void INGAME::updateCurrentMapOrder() {
	Json::Value data = getDataJson();
	if (data["gameplay-status"]["currentmaporder"].asInt() != 5) {
		data["gameplay-status"]["currentmaporder"] = data["gameplay-status"]["currentmaporder"].asInt() + 1;
		std::ofstream fileDataJson("Data/data.json");
		Json::StyledWriter styledwriter;
		fileDataJson << styledwriter.write(data);
		fileDataJson.close();
	}

}

void INGAME::updateMapStatus(){
    Json::Value data = getDataJson();
    int jsonCMOrder = data["gameplay-status"]["currentmaporder"].asInt();
    data["gameplay-status"]["inGameMaps"][jsonCMOrder]["mapStatus"] = true;
    std::ofstream fileDataJson("Data/data.json");
    Json::StyledWriter styledwriter;
    fileDataJson << styledwriter.write(data);
    fileDataJson.close();
}


INGAME::~INGAME(){
	delete MAP1;
	delete MAP2;
	delete MAP3;
	delete MAP4;
	delete MAP5;
	delete MAP6;
}
float INGAME::getScaleCircleCursor() { return scaleCircleCursor; }

void INGAME::notInStateProcess(){/* gameClockTimer.restart();*/ }

void INGAME::loadResources(){
	/* SCALES */
	float screenHeight = sf::VideoMode::getDesktopMode().height;
	scaleCircleCursor = /* 0.33f; */ (screenHeight / maxResolution) * 0.4641f;
	/* CIRCLE CURSOR */
	createSprite(circleTexture, circleSprite, "Assets/001/001-rcs");
	circleSprite.setScale(sf::Vector2f(getScaleCircleCursor(), getScaleCircleCursor()));
	circleSprite.setOrigin(187, 180);
	AnimationCircle = StaticCircleAnimation(&circleTexture, sf::Vector2u(9,1), 0.06f);

	/* PAUSE SCREEN */
	createSprite(pauseTexture, pauseSprite, "Assets/004/004-pse");
	pauseSprite.setScale(sf::Vector2f(getFullScreenSpriteScale(), getFullScreenSpriteScale()));

	screenSize.x = sf::VideoMode::getDesktopMode().width;
	screenSize.y = sf::VideoMode::getDesktopMode().height;

	// Range Resume
	rRangeX[0] = screenSize.x * 0.4502196193;
	rRangeX[1] = screenSize.x * 0.5790629575;
	rRangeY[0] = screenSize.y * 0.4596354167;
	rRangeY[1] = screenSize.y * 0.5247395833;

	//Range Quit
	qRangeX[0] = screenSize.x * 0.4502196193;
	qRangeX[1] = screenSize.x * 0.5790629575;
	qRangeY[0] = screenSize.y * 0.5989583333;
	qRangeY[1] = screenSize.y * 0.6640625;

	/* WALDO FOUND */
	createSprite(waldoFoundTexture, waldoFoundSprite, "Assets/004/004-fnd");
	waldoFoundSprite.setScale(sf::Vector2f(getFullScreenSpriteScale(), getFullScreenSpriteScale()));
	conRangeX[0] = screenSize.x * 0.4436310395;
	conRangeX[1] = screenSize.x * 0.555636896;
	conRangeY[0] = screenSize.y * 0.5911458333;
	conRangeY[1] = screenSize.y * 0.64453125;

	/* GAME OVER */
	createSprite(gameOverTexture, gameOverSprite, "Assets/004/004-go");
	gameOverSprite.setScale(sf::Vector2f(getFullScreenSpriteScale(), getFullScreenSpriteScale()));

	/* IN GAME SOUND EFFECTS */
	// wrong click
	wrongClickBuffer.loadFromFile("Assets/Audio/SoundEffects/WrongClick.wav");
	wrongClickSound.setBuffer(wrongClickBuffer);
	increaseBar(BARUI::barload);

	// waldo fund
	waldoFoundBuffer.loadFromFile("Assets/Audio/SoundEffects/WallyFound.wav");
	waldoFoundSound.setBuffer(waldoFoundBuffer);
	increaseBar(BARUI::barload);

	loadMaps();
}

INGAME::INGAME(): State(), AnimationCircle() { loadResources();}

bool INGAME::resumeInRange(const sf::Vector2i &mousePos){
	return ((mousePos.x >= rRangeX[0] && mousePos.x <= rRangeX[1]) && 
		(mousePos.y >= rRangeY[0] && mousePos.y <= rRangeY[1]));
}

bool INGAME::quitInRange(const sf::Vector2i &mousePos) {
	return ((mousePos.x >= qRangeX[0] && mousePos.x <= qRangeX[1]) &&
		(mousePos.y >= qRangeY[0] && mousePos.y <= qRangeY[1]));
}

bool INGAME::continueInRange(const sf::Vector2i &mousePos){
	return ((mousePos.x >= conRangeX[0] && mousePos.x <= conRangeX[1]) &&
		(mousePos.y >= conRangeY[0] && mousePos.y <= conRangeY[1]));
}

void INGAME::run(sf::RenderWindow *window, const float &dtArg) {
	window->setMouseCursorVisible(false);
	if (gotoMapTriggered){
		/* Will trigger gotoChosenMap() and set gotoMapTriggered
		to false to prevent the function gotoChosenMap from executing over and over again */
		gotoChosenMap();
		gotoMapTriggered = false;
	}
	if (gamePause) { /* PAUSED THE GAME */
		inGameMousePos = sf::Mouse::getPosition(*window);
		window->draw(pauseSprite);

		if (resumeInRange(inGameMousePos)){
			handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			window->draw(handSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if (!mouseDown){
					globalClickSound.play();
					gamePause = false;
					mouseDown = true;
				}
			} else
				mouseDown = false;
		}
		else if (quitInRange(inGameMousePos)){
			handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			window->draw(handSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				globalClickSound.play();
				window->setMouseCursorVisible(true);
				if (MessageBoxA(NULL,"Are you sure you want to go to the main menu?", "Waldo", MB_YESNO) == IDYES){
					CurrentMap->resetMapState();
					CurrentMap->gametimer.moveTextMinutes = false;
					gamePause = false;
					switchingState = "Menu";
					gotoMapTriggered = true;
				}
			}
		} else {
			arrowSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			window->draw(arrowSprite);
			CurrentMap->gametimer.gameClockTimer->restart();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if (!keyDown){
				gamePause = false;
				keyDown = true;
			}
			
		}  else keyDown = false;
	} else { /* PAUSE IS FALSE */
		if (CurrentMap->waldoFound){ /* WALDO IS FOUND */
			inGameMousePos = sf::Mouse::getPosition(*window);
			window->draw(CurrentMap->returnSprite());
			CurrentMap->gametimer.drawTimer(window);
			window->draw(waldoFoundSprite);
			if (continueInRange(inGameMousePos)){
				handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(handSprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!mouseDown){
						CurrentMap->resetMapState();
						CurrentMap->gametimer.moveTextMinutes = false;
						if (currentMapIndex < getDataJson()["gameplay-status"]["currentmaporder"].asUInt()){
							currentMapIndex += 1;
							gotoChosenMap();
						} else {
							updateCurrentMapOrder();
							currentMapIndex = getDataJson()["gameplay-status"]["currentmaporder"].asUInt();
							updateMapStatus();
							SetMapProperty();
						}
						mouseDown = true;
					}
				} else
					mouseDown = false;
			} else {
				arrowSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(arrowSprite);
			}
		} else if (CurrentMap->gameOver){ /* RAN OUT OF TIME */
			inGameMousePos = sf::Mouse::getPosition(*window);
			window->draw(CurrentMap->returnSprite());
			CurrentMap->gametimer.drawTimer(window);
			window->draw(gameOverSprite);
			if (continueInRange(inGameMousePos)){
				handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(handSprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!mouseDown){
						CurrentMap->resetMapState();
						CurrentMap->gametimer.moveTextMinutes = false;
						mouseDown = true;
						switchingState = "Menu";
						gotoMapTriggered = true;
					}
				} else
					mouseDown = false;
			} else {
				arrowSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(arrowSprite);
			}

		} else { /* NEITHER OF THE TWO STATES ABOVE ARE TRUE (WaldoFound, GameOver) - player will continue to find waldo */
			AnimationCircle.Update(AnimationCircle.currentRow, dtArg);
			circleSprite.setTextureRect(AnimationCircle.uvRect);
			
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
				circleSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (!mouseDown){
						if (CurrentMap->checkMouseClick(inGameMousePos)) { /* MOUSE POS IN COORDINATES OF WALDO */
							waldoFoundSound.play();
							CurrentMap->waldoFound = true;
						}
						else wrongClickSound.play(); /* MOUSE NOT IN WALDO COORDINATES */
						mouseDown = true;
					}
				} else
					mouseDown = false;		
			}
			if (CurrentMap->gametimer.seconds == 0 && CurrentMap->gametimer.minutes == 0){
				CurrentMap->gameOver = true;
			}
			
			CurrentMap->gametimer.UpdateTimer();
			window->draw(CurrentMap->returnSprite());
			CurrentMap->gametimer.drawTimer(window);
			window->draw(circleSprite);
		}
	}		
}
