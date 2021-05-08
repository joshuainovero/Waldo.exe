#pragma once

bool MenuActive = true;
bool InGameActive = false;

MapProperty* CurrentMap;

Json::Value getDataJson() {
	std::ifstream fileDataJson("Data/data.json");
		Json::Value data;
		Json::Reader reader;
		reader.parse(fileDataJson, data);
	fileDataJson.close();
	return data;
}

void updateCurrentMapOrder() {
	Json::Value data = getDataJson();
	if (data["currentMapOrder"].asInt() != 5) {
		data["currentMapOrder"] = data["currentMapOrder"].asInt() + 1;
		std::ofstream fileDataJson("Data/data.json");
		Json::StyledWriter styledwriter;
		fileDataJson << styledwriter.write(data);
		fileDataJson.close();
	}

}

void SetMapProperty() {

	switch (getDataJson()["currentMapOrder"].asInt()) {
		case 0: CurrentMap = &MAP1; break;
		case 1: CurrentMap = &MAP2; break;
		case 2: CurrentMap = &MAP3; break;
		case 3: CurrentMap = &MAP4; break;
		case 4: CurrentMap = &MAP5; break;
		case 5: CurrentMap = &MAP6; break;
	}
	intro.music.stop();
	MenuActive = false;
	InGameActive = true;
	CurrentMap->clockRunning = true;
	CurrentMap->clockTimer = new sf::Clock;

}

