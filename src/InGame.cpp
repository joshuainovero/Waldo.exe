#include "InGame.hpp"

/* STATE STACKS */
//Pause -> quit pop
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
	pauseSprite.setOrigin(sf::Vector2f((pauseSprite.getTexture()->getSize().x/5.0f)/2.0f, (pauseSprite.getTexture()->getSize().y/3.0f)/2.0f));
	pauseSprite.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2.0f, sf::VideoMode::getDesktopMode().height / 2.0f));
	AnimationPause = StaticPauseAnimation(&pauseTexture, sf::Vector2u(5,3), 0.009f);
	screenSize.x = sf::VideoMode::getDesktopMode().width;
	screenSize.y = sf::VideoMode::getDesktopMode().height;

	/* QUIT POP UP */
	createSprite(quitTexture, quitSprite, "Assets/004/004-qs");
	quitSprite.setScale(sf::Vector2f(getFullScreenSpriteScale(), getFullScreenSpriteScale()));
	quitSprite.setOrigin(sf::Vector2f(quitSprite.getTexture()->getSize().x/2.0f, quitSprite.getTexture()->getSize().y/2.0f));
	quitSprite.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2.0f, sf::VideoMode::getDesktopMode().height / 2.0f));


	/* CLICK EVENTS */
	// Range resume
	rRangeX[0] = 858.0f * (screenSize.x / 1920.0f);
	rRangeX[1] = (rRangeX[0]) + (203.0f * (screenSize.x / 1920.0f));
	rRangeY[0] = 501.0f * (screenSize.y / 1080.0f);
	rRangeY[1] = (rRangeY[0]) + (54.0f * (screenSize.y / 1080.0f));

	// Range Quit
	qRangeX[0] = 858.0f * (screenSize.x / 1920.0f);
	qRangeX[1] = (qRangeX[0]) + (203.0f * (screenSize.x / 1920.0f));
	qRangeY[0] = 613.0f * (screenSize.y / 1080.0f);
	qRangeY[1] = (qRangeY[0]) + (54.0f * (screenSize.y / 1080.0f));

	// Range Check
	q2RangeX[0] = 855.0f * (screenSize.x / 1920.0f);
	q2RangeX[1] = q2RangeX[0] + (64.0f * (screenSize.x / 1920.0f));
	q2RangeY[0] = 540.0f * (screenSize.y / 1080.0f);
	q2RangeY[1] = q2RangeY[0] + (63.0f * (screenSize.y / 1080.0f));

	// Range ex
	exRangeX[0] = 1005.0f * (screenSize.x / 1920.0f);
	exRangeX[1] = exRangeX[0] + (60.0f * (screenSize.x / 1920.0f));
	exRangeY[0] = 540.0f * (screenSize.y / 1080.0f);
	exRangeY[1] = exRangeY[0] + (60.0f * (screenSize.y / 1080.0f));
	

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

INGAME::INGAME(): State(), AnimationCircle(), AnimationPause() { loadResources();}

bool INGAME::clickEventInRange(float clickRangeX[2], float clickRangeY[2], sf::Vector2i &mousePos){
	return ((mousePos.x >= clickRangeX[0] && mousePos.x <= clickRangeX[1]) &&
		(mousePos.y >= clickRangeY[0] && mousePos.y <= clickRangeY[1]));
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
		AnimationPause.Update(AnimationPause.currentRow, dtArg);
		pauseSprite.setTextureRect(AnimationPause.uvRect);
		inGameMousePos = sf::Mouse::getPosition(*window);
		window->draw(pauseSprite);
		if (quitPop){ /* QUIT CHOICE */
			window->draw(quitSprite); 
			if (clickEventInRange(q2RangeX, q2RangeY, inGameMousePos)){
				handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(handSprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!mouseDown){
						globalClickSound.play();
						CurrentMap->resetMapState();
						CurrentMap->gametimer.moveTextMinutes = false;
						gamePause = false;
						quitPop = false;
						switchingState = "Menu";
						gotoMapTriggered = true;
						AnimationPause.resetState();
						mouseDown = true;
					}
				} else mouseDown = false;
			} else if (clickEventInRange(exRangeX, exRangeY, inGameMousePos)){
				handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(handSprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!mouseDown){
						globalClickSound.play();
						quitPop = false;
						mouseDown = true;
					}
				} else mouseDown = false;
			}
			 else {
				arrowSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(arrowSprite);
			}
		}
		else {
			if (clickEventInRange(rRangeX, rRangeY, inGameMousePos)){
				handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(handSprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!mouseDown){
						globalClickSound.play();
						gamePause = false;
						mouseDown = true;
						AnimationPause.resetState();
					}
				} else
					mouseDown = false;
			}
			else if (clickEventInRange(qRangeX, qRangeY, inGameMousePos)){
				handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(handSprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!mouseDown){
						globalClickSound.play();
						quitPop = true;
						mouseDown = true;
					}
				} else mouseDown = false;
			} else {
				arrowSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(arrowSprite);
				CurrentMap->gametimer.gameClockTimer->restart();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				if (!keyDown){
					gamePause = false;
					keyDown = true;
					AnimationPause.resetState();
				}
				
			}  else keyDown = false;
		}
	} else { /* PAUSE IS FALSE */
		if (CurrentMap->waldoFound){ /* WALDO IS FOUND */
			inGameMousePos = sf::Mouse::getPosition(*window);
			window->draw(CurrentMap->returnSprite());
			CurrentMap->gametimer.drawTimer(window);
			window->draw(waldoFoundSprite);
			if (clickEventInRange(conRangeX, conRangeY, inGameMousePos)){
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
			if (clickEventInRange(conRangeX, conRangeY, inGameMousePos)){
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