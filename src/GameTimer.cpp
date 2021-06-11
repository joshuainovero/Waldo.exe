#include "GameTimer.hpp"

sf::Clock GameClockStruct::gameClockTimer;
bool GameClockStruct::ClockRunning = false;

TimerLabel::TimerLabel(std::string textContent,float textPosX, float textPosY, unsigned int charSize, sf::Color color) {
	font.loadFromFile("Assets/Fonts/Crossten-ExtraBold.ttf");
	text.setFont(font);
	text.setString(textContent);
	text.setFillColor(color);
	text.setPosition(textPosX, textPosY);
	text.setCharacterSize(charSize);

}

TimerLabel timerDisplaySeconds("-", sf::VideoMode::getDesktopMode().width / 2, 40.0, 65, sf::Color::White);
TimerLabel timerDisplayColon(":", (sf::VideoMode::getDesktopMode().width / 2) - 20, 40.0, 65, sf::Color::White);
TimerLabel timerDisplayMinutes("-", (sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 35, 40.0, 65, sf::Color::White);

//Shadow Properties
TimerLabel timerShadowSeconds("-", (sf::VideoMode::getDesktopMode().width / 2) + 5, 45.0, 66, sf::Color::Black);
TimerLabel timerShadowColon(":", (sf::VideoMode::getDesktopMode().width / 2) - 15, 45.0, 66, sf::Color::Black);
TimerLabel timerShadowMinutes("-", ((sf::VideoMode::getDesktopMode().width / 2) - (65 + 20) + 35) + 5, 45.0, 66, sf::Color::Black);


GameTimer::GameTimer(const int mTimerCounts[2])
    :seconds{mTimerCounts[0]}, minutes{mTimerCounts[1]}{
        timerDisplayMinutes.returnText()->setString(std::to_string(minutes));
        timerDisplaySeconds.returnText()->setString(std::to_string(seconds));

        timerShadowMinutes.returnText()->setString(std::to_string(minutes));
        timerShadowSeconds.returnText()->setString(std::to_string(seconds));
    }

void GameTimer::startTimer() {
    GameClockStruct::ClockRunning = true;
}

void GameTimer::stopTimer(){
    GameClockStruct::ClockRunning = false;
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

    timerDisplayMinutes.returnText()->setString(std::to_string(minutes));
    timerShadowMinutes.returnText()->setString(std::to_string(minutes));
    sf::Time elapsed = GameClockStruct::gameClockTimer.getElapsedTime();
    if (static_cast<int>(elapsed.asSeconds()) != tempSeconds){
        tempSeconds = elapsed.asSeconds();
        if (seconds == 0 && minutes != 0){
            seconds = 59;
            minutes--;
        } else 
            seconds--;
    }
   // std::cout << "Elapsed : " << static_cast<int>(elapsed.asSeconds()) << std::endl;
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

int GameTimer::m1TimeCounts[2] = {10,0};
int GameTimer::m2TimeCounts[2] = {40,1};
int GameTimer::m3TimeCounts[2] = {20,1};
int GameTimer::m4TimeCounts[2] = {50,1};
int GameTimer::m5TimeCounts[2] = {35,1};
int GameTimer::m6TimeCounts[2] = {20,2};