#pragma once
#include <json/json.h>
#include <fstream>
#include <unistd.h>

bool checkingForUpdates = true;

//Set temporary sprites for updates
sf::Texture *textureCheckUpdating = new sf::Texture;
sf::Sprite *spriteCheckUpdating = new sf::Sprite;

sf::Texture *textureCheckUpdatingNow = new sf::Texture;
sf::Sprite *spriteCheckUpdatingNow = new sf::Sprite;

sf::Texture *tempArrowCursorTexture = new sf::Texture;
sf::Sprite  *tempArrowCursorSprite = new sf::Sprite;
sf::Vector2i *tempMenuMousePos = new sf::Vector2i;

void freeTemporarySprites() {
	delete spriteCheckUpdating;
	delete spriteCheckUpdatingNow;
	delete tempArrowCursorSprite;
	delete textureCheckUpdating;
	delete textureCheckUpdatingNow;
	delete tempArrowCursorTexture;
}

void updateVersion(){
	std::ifstream fileVersionJSON("version.json");
		Json::Value data;
		Json::Reader reader;
		reader.parse(fileVersionJSON, data);
	fileVersionJSON.close();

    std::ofstream updateVersionJSON("version.json");
        std::ifstream readTransferVersion("updates/transferversion");
            std::string newVersion;
            readTransferVersion >> newVersion;
        readTransferVersion.close();

        data["localversion"] = newVersion;
        Json::StyledWriter styledwriter;
        updateVersionJSON << styledwriter.write(data);
    updateVersionJSON.close();

}

void clientUpdate(sf::RenderWindow *windowPtr){
	windowPtr->setMouseCursorVisible(false);
	*tempMenuMousePos = sf::Mouse::getPosition(*windowPtr);
	tempArrowCursorSprite->setPosition(static_cast<float>(tempMenuMousePos->x), static_cast<float>(tempMenuMousePos->y));
	std::ifstream readUpdateRequired("updates/UpdateRequired");
		std::string checkUpdate;
		readUpdateRequired >> checkUpdate;
		if (checkUpdate != "True"){
			windowPtr->draw(*spriteCheckUpdating);
			windowPtr->draw(*tempArrowCursorSprite);
		}

		if (checkUpdate == "True"){
			windowPtr->draw(*spriteCheckUpdatingNow);
			windowPtr->draw(*tempArrowCursorSprite);
			std::ifstream readState("updates/state");
				std::string updateStatus;
				readState >> updateStatus;
			readState.close();
			if (updateStatus == "Updated"){
				updateVersion();
				std::ofstream writeUpdateRequired("updates/UpdateRequired");
					writeUpdateRequired << "ND";
				writeUpdateRequired.close();
				std::ofstream writeState("updates/state");
					writeState << "None";
				writeState.close();
				checkingForUpdates = false;
				freeTemporarySprites();
				system("TASKKILL /F /IM woUpdate.exe 2>NULL");
				//system("cd updates && start extract.exe");
			}

		}
		else if (checkUpdate == "False"){
			checkingForUpdates = false;
			std::ofstream writeUpdateRequired("updates/UpdateRequired");
				writeUpdateRequired << "ND";
			writeUpdateRequired.close();
			freeTemporarySprites();
			system("TASKKILL /F /IM woUpdate.exe 2>NULL");
		}
}

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

void getMainDirectory(){
    char tmp[256];
    getcwd(tmp, 256);
	std::string path = tmp;
    Json::Value data = getDataJson();
    data["MainDirectory"] = path;

    std::ofstream fileDataJson("Data/data.json");
	    Json::StyledWriter styledwriter;
	    fileDataJson << styledwriter.write(data);
	fileDataJson.close();
}

