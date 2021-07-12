#pragma once
#include <SFML/Graphics.hpp>
#include "TimerLabel.hpp"

struct GameTimer{

    int seconds, minutes, tempSeconds;
    // bool ClockRunning;
    bool moveTextMinutes;
    sf::Clock *gameClockTimer;

    TimerLabel timerDisplaySeconds;
    TimerLabel timerDisplayColon;
    TimerLabel timerDisplayMinutes;

    //Shadow
    TimerLabel timerShadowSeconds;
    TimerLabel timerShadowColon;
    TimerLabel timerShadowMinutes;

    GameTimer(const std::array<int, 2> &mTimerCounts);
    void startTimer();
    void stopTimer();
    void UpdateTimer();
    void drawTimer(sf::RenderWindow *winPtrTimer);
    // void getElapsedFromInGame(const sf::Time &t);
    // sf::Time elapsedTimeFromInGame;

	int m1TimeCounts[2] = {30,1};
    int m2TimeCounts[2] = {10,1};
    int m3TimeCounts[2] = {5,2};
    int m4TimeCounts[2] = {30,2};
    int m5TimeCounts[2] = {45,0};
    int m6TimeCounts[2] = {20,2};
};
