#pragma once
#include <SFML/Graphics.hpp>

class TimerLabel {
private:
	sf::Text text;
	sf::Font font;

public:
    static bool moveTextMinutes;
	sf::Text *returnText() { return &text; }
	TimerLabel(std::string textContent, float textPosX, float textPosY, unsigned int charSize, sf::Color);
	void moveText(int x, int y) { text.move(x, y); }
};

struct GameClockStruct {
    static sf::Clock gameClockTimer;
    static bool ClockRunning;
};

struct GameTimer{

    int seconds, minutes, tempSeconds;

    GameTimer(const int mTimerCounts[2]);
    void startTimer();
    void stopTimer();
    void UpdateTimer();
    void drawTimer(sf::RenderWindow *winPtrTimer);

    static int m1TimeCounts[2];
    static int m2TimeCounts[2];
    static int m3TimeCounts[2];
    static int m4TimeCounts[2];
    static int m5TimeCounts[2];
    static int m6TimeCounts[2];
};
