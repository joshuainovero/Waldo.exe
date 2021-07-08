#pragma once
#include <memory>
class INGAME : public State{
private:
	sf::Texture circleTexture, pauseTexture, waldoFoundTexture, gameOverTexture;
	sf::Sprite circleSprite, pauseSprite, waldoFoundSprite, gameOverSprite;
	sf::SoundBuffer wrongClickBuffer, waldoFoundBuffer;
	sf::Sound wrongClickSound, waldoFoundSound;
	StaticObjAnimation AnimationCircle;
	sf::Vector2i inGameMousePos;
	sf::Vector2i screenSize;
	float scaleCircleCursor;
	int rRangeX[2], rRangeY[2];
	//615 -> 791         353 -> 403
	int qRangeX[2], qRangeY[2];
	//615 -> 791         460 -> 510

	int conRangeX[2], conRangeY[2];
	bool gamePause = false;
	bool keyDown = false;

public:
	INGAME();
	virtual ~INGAME();
	virtual void run(sf::RenderWindow *window, const float &dtArg) override;
	virtual void loadResources() override;
	float getScaleCircleCursor();
	bool resumeInRange(const sf::Vector2i &mousePos);
	bool quitInRange(const sf::Vector2i &mousePos);
	bool continueInRange(const sf::Vector2i &mousePos);

	static MapProperty* CurrentMap;
	static uint32_t currentMapIndex;

	static MapProperty *MAP1;
	static MapProperty *MAP2;
	static MapProperty *MAP3;
	static MapProperty *MAP4;
	static MapProperty *MAP5;
	static MapProperty *MAP6;

	static void SetMapProperty();
	static void loadMaps();
	static void gotoChosenMap(const int &mapIndex);
};
MapProperty *INGAME::CurrentMap;
uint32_t INGAME::currentMapIndex;

MapProperty *INGAME::MAP1;
MapProperty *INGAME::MAP2;
MapProperty *INGAME::MAP3;
MapProperty *INGAME::MAP4;
MapProperty *INGAME::MAP5;
MapProperty *INGAME::MAP6;

void INGAME::loadMaps(){
	INGAME::MAP1 = new MapProperty("Assets/003/003-m1", "Map1", GameTimer::m1TimeCounts);
	INGAME::MAP2 = new MapProperty("Assets/003/003-m2", "Map2", GameTimer::m2TimeCounts);
	INGAME::MAP3 = new MapProperty("Assets/003/003-m3", "Map3", GameTimer::m3TimeCounts);
	INGAME::MAP4 = new MapProperty("Assets/003/003-m4", "Map4", GameTimer::m4TimeCounts);
	INGAME::MAP5 = new MapProperty("Assets/003/003-m5", "Map5", GameTimer::m5TimeCounts);
	INGAME::MAP6 = new MapProperty("Assets/003/003-m6", "Map6", GameTimer::m6TimeCounts);
}

void INGAME::SetMapProperty() {
	switch (getDataJson()["gameplay-status"]["currentmaporder"].asInt()) {
		case 0: INGAME::CurrentMap = INGAME::MAP1; break;
		case 1: INGAME::CurrentMap = INGAME::MAP2; break;
		case 2: INGAME::CurrentMap = INGAME::MAP3; break;
		case 3: INGAME::CurrentMap = INGAME::MAP4; break;
		case 4: INGAME::CurrentMap = INGAME::MAP5; break;
		case 5: INGAME::CurrentMap = INGAME::MAP6; break;
	}
	// Intromusic->music.stop();
	State::states.at(0)->stopCurrentMusicPlaying();
	GameClockStruct::ClockRunning = true;

}

void INGAME::gotoChosenMap(const int &mapIndex){
	switch (mapIndex){
		case 0: INGAME::CurrentMap = INGAME::MAP1; break;
		case 1: INGAME::CurrentMap = INGAME::MAP2; break;
		case 2: INGAME::CurrentMap = INGAME::MAP3; break;
		case 3: INGAME::CurrentMap = INGAME::MAP4; break;
		case 4: INGAME::CurrentMap = INGAME::MAP5; break;
		case 5: INGAME::CurrentMap = INGAME::MAP6; break;
	}
	// Intromusic->music.stop();
	State::states.at(0)->stopCurrentMusicPlaying();
	State::currentState = State::states.at(2);
	GameClockStruct::ClockRunning = true;
}

INGAME::~INGAME(){
	delete INGAME::MAP1;
	delete INGAME::MAP2;
	delete INGAME::MAP3;
	delete INGAME::MAP4;
	delete INGAME::MAP5;
	delete INGAME::MAP6;
}
float INGAME::getScaleCircleCursor() { return scaleCircleCursor; }

void INGAME::loadResources(){
	/* SCALES */
	float screenHeight = sf::VideoMode::getDesktopMode().height;
	scaleCircleCursor = /* 0.33f; */ (screenHeight / maxResolution) * 0.4641f;
	/* CIRCLE CURSOR */
	createSprite(circleTexture, circleSprite, "Assets/001/001-rcs");
	circleSprite.setScale(sf::Vector2f(getScaleCircleCursor(), getScaleCircleCursor()));
	circleSprite.setOrigin(187, 180);
	AnimationCircle = StaticObjAnimation(&circleTexture, sf::Vector2u(9,1), 0.06f);

	/* PAUSE SCREEN */
	createSprite(pauseTexture, pauseSprite, "Assets/004/004-pse");
	pauseSprite.setScale(sf::Vector2f(State::getFullScreenSpriteScale(), State::getFullScreenSpriteScale()));

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
	waldoFoundSprite.setScale(sf::Vector2f(State::getFullScreenSpriteScale(), State::getFullScreenSpriteScale()));
	conRangeX[0] = screenSize.x * 0.4436310395;
	conRangeX[1] = screenSize.x * 0.555636896;
	conRangeY[0] = screenSize.y * 0.5911458333;
	conRangeY[1] = screenSize.y * 0.64453125;

	/* GAME OVER */
	createSprite(gameOverTexture, gameOverSprite, "Assets/004/004-go");
	gameOverSprite.setScale(sf::Vector2f(State::getFullScreenSpriteScale(), State::getFullScreenSpriteScale()));

	/* IN GAME SOUND EFFECTS */
	// wrong click
	wrongClickBuffer.loadFromFile("Assets/Audio/SoundEffects/WrongClick.wav");
	wrongClickSound.setBuffer(wrongClickBuffer);
	increaseBar(BARUI::barload);

	// waldo fund
	waldoFoundBuffer.loadFromFile("Assets/Audio/SoundEffects/WallyFound.wav");
	waldoFoundSound.setBuffer(waldoFoundBuffer);
	increaseBar(BARUI::barload);
}

INGAME::INGAME(){loadResources();}

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
	if (gamePause) {
		inGameMousePos = sf::Mouse::getPosition(*window);
		window->draw(pauseSprite);

		if (resumeInRange(inGameMousePos)){
			State::handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			window->draw(State::handSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if (!Engine::mouseDown){
					globalClickSound.play();
					gamePause = false;
					Engine::mouseDown = true;
				}
			} else
				Engine::mouseDown = false;
		}
		else if (quitInRange(inGameMousePos)){
			State::handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			window->draw(State::handSprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				globalClickSound.play();
				window->setMouseCursorVisible(true);
				if (MessageBoxA(NULL,"Are you sure you want to go to the main menu?", "Waldo", MB_YESNO) == IDYES){
					INGAME::CurrentMap->gametimer.stopTimer();
					INGAME::CurrentMap->resetMapState();
					TimerLabel::moveTextMinutes = false;
					gamePause = false;
					currentState = states.at(0);
				}
			}
		} else {
			State::arrowSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
			window->draw(State::arrowSprite);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if (!keyDown){
				gamePause = false;
				keyDown = true;
			}
			
		}  else keyDown = false;
		GameClockStruct::gameClockTimer.restart();
	} else {
		if (INGAME::CurrentMap->waldoFound){
			inGameMousePos = sf::Mouse::getPosition(*window);
			window->draw(INGAME::CurrentMap->returnSprite());
			INGAME::CurrentMap->gametimer.drawTimer(window);
			window->draw(waldoFoundSprite);
			if (continueInRange(inGameMousePos)){
				State::handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(State::handSprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!Engine::mouseDown){
						GameClockStruct::gameClockTimer.restart();
						INGAME::CurrentMap->resetMapState();
						TimerLabel::moveTextMinutes = false;
						if (INGAME::currentMapIndex < getDataJson()["gameplay-status"]["currentmaporder"].asUInt()){
							INGAME::currentMapIndex += 1;
							INGAME::gotoChosenMap(INGAME::currentMapIndex);
						} else {
							updateCurrentMapOrder();
							INGAME::currentMapIndex = getDataJson()["gameplay-status"]["currentmaporder"].asUInt();
							updateMapStatus();
							INGAME::SetMapProperty();
						}
						Engine::mouseDown = true;
					}
				} else
					Engine::mouseDown = false;
			} else {
				State::arrowSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(State::arrowSprite);
			}
		} else if (INGAME::CurrentMap->gameOver){
			inGameMousePos = sf::Mouse::getPosition(*window);
			window->draw(INGAME::CurrentMap->returnSprite());
			INGAME::CurrentMap->gametimer.drawTimer(window);
			window->draw(gameOverSprite);
			if (continueInRange(inGameMousePos)){
				State::handSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(State::handSprite);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					if (!Engine::mouseDown){
						INGAME::CurrentMap->resetMapState();
						TimerLabel::moveTextMinutes = false;
						Engine::mouseDown = true;
						currentState = states.at(0);
					}
				} else
					Engine::mouseDown = false;
			} else {
				State::arrowSprite.setPosition(static_cast<float>(inGameMousePos.x), static_cast<float>(inGameMousePos.y));
				window->draw(State::arrowSprite);
			}

		} else {
			AnimationCircle.Update(AnimationCircle.currentRow, dtArg);
			circleSprite.setTextureRect(AnimationCircle.uvRect);
			
			if (Engine::appInFocus(window)){
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
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // If wally is found
					if (!Engine::mouseDown){
						if (INGAME::CurrentMap->checkMouseClick(inGameMousePos)) {
							waldoFoundSound.play();
							INGAME::CurrentMap->waldoFound = true;
							if (GameClockStruct::ClockRunning) {
								GameClockStruct::ClockRunning = false;
							}
						}
						else wrongClickSound.play();
						Engine::mouseDown = true;
					}
				} else
					Engine::mouseDown = false;		
			}
			if (INGAME::CurrentMap->gametimer.seconds == -1 && INGAME::CurrentMap->gametimer.minutes == 0){
				INGAME::CurrentMap->gametimer.stopTimer();
				INGAME::CurrentMap->gameOver = true;
			}
			
			if (GameClockStruct::ClockRunning)
				INGAME::CurrentMap->gametimer.UpdateTimer();

			window->draw(INGAME::CurrentMap->returnSprite());
			window->draw(circleSprite);
			INGAME::CurrentMap->gametimer.drawTimer(window);
		}
	}		
}
