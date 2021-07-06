#pragma once

MapProperty* CurrentMap;
int currentMapIndex;

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
		case 0: CurrentMap = MAP1; break;
		case 1: CurrentMap = MAP2; break;
		case 2: CurrentMap = MAP3; break;
		case 3: CurrentMap = MAP4; break;
		case 4: CurrentMap = MAP5; break;
		case 5: CurrentMap = MAP6; break;
	}
	Intromusic->music.stop();
	GameClockStruct::ClockRunning = true;

}

void gotoChosenMap(const int &mapIndex){
	switch (mapIndex){
		case 0: CurrentMap = MAP1; break;
		case 1: CurrentMap = MAP2; break;
		case 2: CurrentMap = MAP3; break;
		case 3: CurrentMap = MAP4; break;
		case 4: CurrentMap = MAP5; break;
		case 5: CurrentMap = MAP6; break;
	}
	Intromusic->music.stop();
	State::currentState = State::states.at(2);
	GameClockStruct::ClockRunning = true;
}

