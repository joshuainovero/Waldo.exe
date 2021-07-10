#pragma once
#include <memory>
#include "State.hpp"
#include "MapProperties.hpp"
#include "StaticObjAnimation.hpp"

class INGAME : public State{
private:
	sf::Texture circleTexture, pauseTexture, waldoFoundTexture, gameOverTexture;
	sf::Sprite circleSprite, pauseSprite, waldoFoundSprite, gameOverSprite;
	sf::SoundBuffer wrongClickBuffer, waldoFoundBuffer;
	sf::Sound wrongClickSound, waldoFoundSound;
	StaticObjAnimation AnimationCircle;
	sf::Vector2i inGameMousePos;
	sf::Vector2i screenSize;
	uint32_t currentMapIndex;
	sf::Clock gameClockTimer;
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
	virtual void notInStateProcess() override;
	void updateCurrentMapOrder();
	float getScaleCircleCursor();
	bool resumeInRange(const sf::Vector2i &mousePos);
	bool quitInRange(const sf::Vector2i &mousePos);
	bool continueInRange(const sf::Vector2i &mousePos);

	MapProperty* CurrentMap;
	MapProperty *MAP1;
	MapProperty *MAP2;
	MapProperty *MAP3;
	MapProperty *MAP4;
	MapProperty *MAP5;
	MapProperty *MAP6;

	void SetMapProperty();
	void updateMapStatus();
	void loadMaps();
	void gotoChosenMap();
};
