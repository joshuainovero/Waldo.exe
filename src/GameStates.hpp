#pragma once

bool MenuActive = true;
bool InGameActive = false;
int delayInGameClick;

MapProperty* CurrentMap;

bool appInFocus(sf::RenderWindow* app){
    if(app == NULL)
        return false;

    HWND handle = app->getSystemHandle();
    bool one = handle == GetFocus();
    bool two = handle == GetForegroundWindow();

    if(one != two){
        SetFocus(handle);
        SetForegroundWindow(handle);
    }

    return one && two;
}


void SetMapProperty() {
	switch (getDataJson()["gameplay-status"]["currentmaporder"].asInt()) {
		case 0: CurrentMap = &MAP1; break;
		case 1: CurrentMap = &MAP2; break;
		case 2: CurrentMap = &MAP3; break;
		case 3: CurrentMap = &MAP4; break;
		case 4: CurrentMap = &MAP5; break;
		case 5: CurrentMap = &MAP6; break;
	}
	Intromusic.music.stop();
	MenuActive = false;
	InGameActive = true;
	GameClockStruct::ClockRunning = true;
	delayInGameClick = CurrentMap->gametimer.seconds - 2;

}

void gameEvents(sf::RenderWindow *currentWindow){
	sf::Event windowEvent;
		while (currentWindow->pollEvent(windowEvent)) {
			switch (windowEvent.type) {
			case sf::Event::TextEntered:
				if (windowEvent.text.unicode == 27)
					currentWindow->close(); 
				break;
			case sf::Event::Closed:
				currentWindow->close(); 
				break;
			default: break;
			}
		}
}

