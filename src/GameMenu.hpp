#pragma once
#include "State.hpp"
#include "TypeWriter.hpp"
#include "Labels.hpp"

class GAMEMENU : public State {
private:
	sf::Texture menuPageTexture, exitIconTexture, openingTexture;
	sf::Sprite menuPageSprite, exitIconSprite, openingSprite;
	sf::Music menuMusic;
	ButtonLabel* startButton;
	ButtonLabel* startButtonBorder;
	ButtonLabel* startButtonShadow;
	TypeWriter openingWriter;
	float scaleExitIcon;

	int rangeExitX[2], rangeExitY[2];
	float exitWidth, exitHeight;

	bool stateOpening = false;
	size_t currentDialogueIndex = 0;
	sf::Vector2i menuMousePos;

	const std::array<std::string, 3> openingDialogues{
		"Hello there, gamer! My name is Waldo, and I'm from\nthe Land of Waldos, a land populated by Waldos just\nlike me. You've probably come across me in one of your\nbooks where I'm hidden in various pages",
		"You had a hard time finding me before, didn't you?\nAnyways, I am always ready for an adventure with my\nwalking stick in hand, and my trusty dog Woof by my\nside. I've gotten a little more sophisticated, and I'm\nnow lurking and hidden behind your computer screen.",
		"The rule is straightforward gamer. All you have to do is\nto find me on each map of the game. Simple isn't it? Be\nsure to find me before the clock runs out or else there\nwill be consequences. Best of luck gamer!"
	};

public:
	GAMEMENU();
	void stopMenuMusic() {menuMusic.stop();}
	void eliminateNewGame();
	float getScaleExitIcon();
	virtual void run(sf::RenderWindow *window, const float &dtArg) override;
	virtual void loadResources() override;
	virtual void notInStateProcess() override;
};