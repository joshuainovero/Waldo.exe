#include "GameTimer.hpp"
#include <iostream>

GameTimer::GameTimer(const std::array<int, 2> &mTimerCounts)
    :seconds{mTimerCounts[0]}, minutes{mTimerCounts[1]},
    timerDisplaySeconds("-", sf::VideoMode::getDesktopMode().width / 2, 40.0, 65, sf::Color::White),
    timerDisplayColon(":", (sf::VideoMode::getDesktopMode().width / 2) - 20, 40.0, 65, sf::Color::White),
    timerDisplayMinutes("-", ((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 35), 40.0, 65, sf::Color::White),
    timerShadowSeconds("-", (sf::VideoMode::getDesktopMode().width / 2) + 5, 45.0, 66, sf::Color::Black),
    timerShadowColon(":", (sf::VideoMode::getDesktopMode().width / 2) - 15, 45.0, 66, sf::Color::Black),
    timerShadowMinutes("-", ((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 40), 45.0, 66, sf::Color::Black){
        timerDisplayMinutes.returnText()->setString(std::to_string(minutes));
        timerDisplaySeconds.returnText()->setString(std::to_string(seconds));

        timerShadowMinutes.returnText()->setString(std::to_string(minutes));
        timerShadowSeconds.returnText()->setString(std::to_string(seconds));

        moveTextMinutes = false;
    }

void GameTimer::startTimer() {
    gameClockTimer = new sf::Clock();
    #ifdef DEBUG
    std::cout << "STARTED A NEW TIMER" << std::endl;
    #endif
}

void GameTimer::stopTimer(){
    delete gameClockTimer;
    gameClockTimer = nullptr;
    #ifdef DEBUG
    std::cout << "FREED A TIMER" << std::endl;
    #endif
}

void GameTimer::UpdateTimer(){
    if (seconds < 10){
        timerShadowSeconds.returnText()->setString("0" + std::to_string(seconds));
        timerDisplaySeconds.returnText()->setString("0" + std::to_string(seconds));
    } else {
        if (seconds == 60){
            timerShadowSeconds.returnText()->setString("00");
            timerDisplaySeconds.returnText()->setString("00");
        } else {
            timerShadowSeconds.returnText()->setString(std::to_string(seconds));
            timerDisplaySeconds.returnText()->setString(std::to_string(seconds));
        }
    }
    if (minutes > 1){
        if (!moveTextMinutes) {
            timerDisplayMinutes.returnText()->setPosition(((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 35) - 10, 40.0);
            timerShadowMinutes.returnText()->setPosition(((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 40) - 10, 45.0);
            moveTextMinutes = true;
        }
    } else {
        if (moveTextMinutes){
            timerDisplayMinutes.returnText()->setPosition(((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 35), 40.0);
            timerShadowMinutes.returnText()->setPosition(((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 40), 45.0); 
            moveTextMinutes = false;
        }
    }
    timerDisplayMinutes.returnText()->setString(std::to_string(minutes));
    timerShadowMinutes.returnText()->setString(std::to_string(minutes));
    sf::Time elapsed = gameClockTimer->getElapsedTime();
    if (static_cast<int>(elapsed.asSeconds()) != tempSeconds){
        tempSeconds = elapsed.asSeconds();
        if (seconds == 0 && minutes != 0){
            seconds = 59;
            minutes--;
        } else 
            seconds--;
    }
}

void GameTimer::drawTimer(sf::RenderWindow *winPtrTimer){
    if (minutes == 0){
        winPtrTimer->draw(*timerShadowSeconds.returnText());
        winPtrTimer->draw(*timerShadowColon.returnText());
        
        winPtrTimer->draw(*timerDisplaySeconds.returnText());
        winPtrTimer->draw(*timerDisplayColon.returnText());
    } else {
    //Shadow Timer
        winPtrTimer->draw(*timerShadowSeconds.returnText());
        winPtrTimer->draw(*timerShadowColon.returnText());
        winPtrTimer->draw(*timerShadowMinutes.returnText());

        //Actual Timer
        winPtrTimer->draw(*timerDisplaySeconds.returnText());
        winPtrTimer->draw(*timerDisplayColon.returnText());
        winPtrTimer->draw(*timerDisplayMinutes.returnText());
    }
}