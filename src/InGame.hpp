#pragma once
#include <memory>
#include "State.hpp"
#include "MapProperties.hpp"
#include "StaticCircleAnimation.hpp"

class INGAME : public State{
private:
	sf::Texture circleTexture, pauseTexture, waldoFoundTexture, gameOverTexture;
	sf::Sprite circleSprite, pauseSprite, waldoFoundSprite, gameOverSprite;
	sf::SoundBuffer wrongClickBuffer, waldoFoundBuffer;
	sf::Sound wrongClickSound, waldoFoundSound;
	StaticCircleAnimation AnimationCircle;
	MapProperty* CurrentMap;
	MapProperty *MAP1, *MAP2, *MAP3, *MAP4, *MAP5, *MAP6;
	sf::Vector2i inGameMousePos;
	sf::Vector2i screenSize;
	uint32_t currentMapIndex;
	// sf::Clock gameClockTimer;
	float scaleCircleCursor;
	int rRangeX[2], rRangeY[2]; //615 -> 791         353 -> 403
	int qRangeX[2], qRangeY[2]; //615 -> 791         460 -> 510
	int conRangeX[2], conRangeY[2];
	bool gamePause = false;
	bool keyDown = false;
	bool gotoMapTriggered = true;

private:
	virtual void loadResources() override;
	float getScaleCircleCursor();
	bool resumeInRange(const sf::Vector2i &mousePos);
	bool quitInRange(const sf::Vector2i &mousePos);
	bool continueInRange(const sf::Vector2i &mousePos);
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
