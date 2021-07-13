#include "State.hpp"
#include <Windows.h>

float State::getFullScreenSpriteScale() { return fullScreenSpriteScale; }
float State::getScaleArrow() { return scaleArrow; }

void State::createSprite(sf::Texture &textureP, sf::Sprite &spriteP, const std::string &pathF){
    try {
        std::ifstream checkValidAsset(pathF);
        if (!checkValidAsset)
            throw pathF;
        EDassets::decryptFile(pathF);
        increaseBar(BARUI::barload);
        textureP.loadFromFile("Assets/sprite.png");
        spriteP.setTexture(textureP);
        increaseBar(BARUI::barload);
    } catch (const std::string &threw){
    	if (MessageBoxA(NULL,"An asset has been corrupted or deleted. Please reinstall", "Waldo", MB_ICONERROR) == IDOK){
            std::ofstream emptySpriteFile("Assets/sprite.png", std::ios::binary);
			abort();
        }
    }
}

Json::Value State::getDataJson() {
	std::ifstream fileDataJson("Data/data.json");
		Json::Value data;
		Json::Reader reader;
		reader.parse(fileDataJson, data);
	fileDataJson.close();
	return data;
}

bool State::appInFocus(sf::RenderWindow* app){
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

void State::stopCurrentMusicPlaying(){
    currentMusic->stop();
}

State::State(){
    // Scales
    maxResolution = 1080.0f;
    float screenHeightTemp = sf::VideoMode::getDesktopMode().height;
    State::fullScreenSpriteScale = /*0.714f;*/ screenHeightTemp / maxResolution;
	State::scaleArrow = /* 0.30f; */ (screenHeightTemp / maxResolution) * 0.42f;

	createSprite(arrowTexture, arrowSprite, "Assets/001/001-ac");
	State::arrowSprite.setScale(sf::Vector2f(getScaleArrow(), getScaleArrow()));
	State::arrowSprite.setOrigin(68, 23);

	// Hand cursor
	createSprite(State::handTexture, State::handSprite, "Assets/001/001-hc");
	State::handSprite.setScale(sf::Vector2f(getScaleArrow(), getScaleArrow()));
	State::handSprite.setOrigin(110, 30);

	// Global click sound effect
	globalClickBuffer.loadFromFile("Assets/Audio/SoundEffects/MenuSelection.wav");
	globalClickSound.setBuffer(globalClickBuffer);
	increaseBar(BARUI::barload);
    #ifdef DEBUG
    std::cout << "State loaded" << std::endl;
    #endif


}

State::~State(){
    // Json::Value data = getDataJson();
    // data["gameplay-status"]["gotomap"]["triggered"] = "SHIT";
    // std::ofstream fileDataJson("Data/data.json");
    // Json::StyledWriter styledwriter;
    // fileDataJson << styledwriter.write(data);
    // fileDataJson.close();
}