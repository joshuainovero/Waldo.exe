#pragma once
#include <memory>
#include "State.hpp"
#include "MapProperties.hpp"
#include "StaticCircleAnimation.hpp"
#include "StaticPauseAnimation.hpp"

class INGAME : public State{
private:
	sf::Texture circleTexture, pauseTexture, quitTexture, waldoFoundTexture, gameOverTexture;
	sf::Sprite circleSprite, pauseSprite, quitSprite, waldoFoundSprite, gameOverSprite;
	sf::SoundBuffer wrongClickBuffer, waldoFoundBuffer;
	sf::Sound wrongClickSound, waldoFoundSound;
	StaticCircleAnimation AnimationCircle;
	StaticPauseAnimation AnimationPause;
	MapProperty* CurrentMap;
	MapProperty *MAP1, *MAP2, *MAP3, *MAP4, *MAP5, *MAP6;
	sf::Vector2i inGameMousePos;
	sf::Vector2i screenSize;
	uint32_t currentMapIndex;
	// sf::Clock gameClockTimer;
	float scaleCircleCursor;
	float rRangeX[2], rRangeY[2]; //615 -> 791         353 -> 403
	float qRangeX[2], qRangeY[2]; //615 -> 791         460 -> 510
	float q2RangeX[2], q2RangeY[2]; // Are you sure you want to quit?
	float exRangeX[2], exRangeY[2];
	float conRangeX[2], conRangeY[2];
	bool gamePause = false;
	bool quitPop = false;
	bool keyDown = false;
	bool gotoMapTriggered = true;

private:
	virtual void loadResources() override;
	float getScaleCircleCursor();
	bool clickEventInRange(float clickRangeX[2], float clickRangeY[2], sf::Vector2i &mousePos);
	void updateCurrentMapOrder();
	void SetMapProperty();
	void updateMapStatus();
	void loadMaps();
	void gotoChosenMap();

public:
	INGAME();
	virtual ~INGAME();
	virtual void run(sf::RenderWindow *window, const float &dtArg) override;
	virtual void notInStateProcess() override;
};
