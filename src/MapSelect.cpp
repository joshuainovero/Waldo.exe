#include "MapSelect.hpp"

void MAPSELECT::loadResources(){
    mapSelectResol.x = sf::VideoMode::getDesktopMode().width;
    mapSelectResol.y = sf::VideoMode::getDesktopMode().height;

    //* UNKNOWN ICONS */
    createSprite(ukTexture, ukSprite, "Assets/004/004-uk");
    ukSprite.setScale(sf::Vector2f(getFullScreenSpriteScale(), getFullScreenSpriteScale()));

    /* MAP OPTIONS */
    createSprite(mapOptionsTexture, mapOptionsSprite, "Assets/004/004-mo");
    mapOptionsSprite.setScale(sf::Vector2f(getFullScreenSpriteScale(), getFullScreenSpriteScale()));
}

MAPSELECT::MAPSELECT():State(){ loadResources(); }

bool MAPSELECT::isMapHover(const int &jsonMapIndex, size_t ith){
    return ((MapSelectMousePos.x >= mapSelectResol.x*ukscales[ith][0] && MapSelectMousePos.x <= (mapSelectResol.x * ukscales[ith][0]) + mapSelectResol.x * 401/1920) &&
        (MapSelectMousePos.y >= mapSelectResol.y*ukscales[ith][1] && MapSelectMousePos.y <= (mapSelectResol.y * ukscales[ith][1]) + mapSelectResol.y * 223/1080))
        && getDataJson()["gameplay-status"]["inGameMaps"][jsonMapIndex]["mapStatus"].asBool();
}

void MAPSELECT::notInStateProcess(){}

void MAPSELECT::run(sf::RenderWindow *window, const float &dtArg){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        switchingState = "Menu";
    }
    window->draw(mapOptionsSprite);
    for (size_t i = getDataJson()["gameplay-status"]["currentmaporder"].asUInt() + 1; i < ukscales.size(); ++i){
        ukSprite.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width * ukscales[i][0], sf::VideoMode::getDesktopMode().height * ukscales[i][1]));
        window->draw(ukSprite);
    }
    if (appInFocus(window)){
        MapSelectMousePos = sf::Mouse::getPosition(*window);

        if (isMapHover(0, 0) || isMapHover(1, 1) || isMapHover(2, 2) || isMapHover(3, 3) || isMapHover(4, 4) || isMapHover(5, 5)){
            handSprite.setPosition(static_cast<float>(MapSelectMousePos.x), static_cast<float>(MapSelectMousePos.y));
            window->draw(handSprite);
        } else {
            arrowSprite.setPosition(static_cast<float>(MapSelectMousePos.x), static_cast<float>(MapSelectMousePos.y));
        // ArrowCursorObj->sprite.setPosition((mapSelectResol.x * UkMapObj->ukscales[0][0]) + mapSelectResol.x * 401/1920, (mapSelectResol.y * UkMapObj->ukscales[0][1]) + mapSelectResol.y * 223/1080);
            window->draw(arrowSprite);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (!mouseDown){
                if (isMapHover(0, 0)){
                    globalClickSound.play();

                    Json::Value data = getDataJson();
                    data["gameplay-status"]["gotomap"]["index"] = 0;
                    std::ofstream fileDataJson("Data/data.json");
		            Json::StyledWriter styledwriter;
		            fileDataJson << styledwriter.write(data);
		            fileDataJson.close();
                    switchingState = "InGame";
                }
                else if (isMapHover(1, 1)){
                    globalClickSound.play();

                    Json::Value data = getDataJson();
                    data["gameplay-status"]["gotomap"]["index"] = 1;
                    std::ofstream fileDataJson("Data/data.json");
		            Json::StyledWriter styledwriter;
		            fileDataJson << styledwriter.write(data);
		            fileDataJson.close();
                    switchingState = "InGame";
                }
                else if (isMapHover(2, 2)){
                    globalClickSound.play();

                    Json::Value data = getDataJson();
                    data["gameplay-status"]["gotomap"]["index"] = 2;
                    std::ofstream fileDataJson("Data/data.json");
		            Json::StyledWriter styledwriter;
		            fileDataJson << styledwriter.write(data);
		            fileDataJson.close();
                    switchingState = "InGame";
                }
                else if (isMapHover(3, 3)){
                    globalClickSound.play();
                    
                    Json::Value data = getDataJson();
                    data["gameplay-status"]["gotomap"]["index"] = 3;
                    std::ofstream fileDataJson("Data/data.json");
		            Json::StyledWriter styledwriter;
		            fileDataJson << styledwriter.write(data);
                    switchingState = "InGame";
                }
                else if (isMapHover(4, 4)){
                    globalClickSound.play();

                    Json::Value data = getDataJson();
                    data["gameplay-status"]["gotomap"]["index"] = 4;
                    std::ofstream fileDataJson("Data/data.json");
		            Json::StyledWriter styledwriter;
		            fileDataJson << styledwriter.write(data);
                    switchingState = "InGame";
                }
                else if (isMapHover(5, 5)){
                    globalClickSound.play();

                    Json::Value data = getDataJson();
                    data["gameplay-status"]["gotomap"]["index"] = 5;
                    std::ofstream fileDataJson("Data/data.json");
		            Json::StyledWriter styledwriter;
		            fileDataJson << styledwriter.write(data);
                    switchingState = "InGame";
                }
                mouseDown = true;
            } 
        } else
            mouseDown = false;
    }   
}
