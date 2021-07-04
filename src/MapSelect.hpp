#pragma once


sf::Vector2i MapSelectMousePos;
sf::Vector2f mapSelectResol(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

bool isMapHover(const int &jsonMapIndex, size_t ith){
    return ((MapSelectMousePos.x >= mapSelectResol.x*UkMapObj->ukscales[ith][0] && MapSelectMousePos.x <= (mapSelectResol.x * UkMapObj->ukscales[ith][0]) + mapSelectResol.x * 401/1920) &&
        (MapSelectMousePos.y >= mapSelectResol.y*UkMapObj->ukscales[ith][1] && MapSelectMousePos.y <= (mapSelectResol.y * UkMapObj->ukscales[ith][1]) + mapSelectResol.y * 223/1080))
        && getDataJson()["gameplay-status"]["inGameMaps"][jsonMapIndex]["mapStatus"].asBool();
}

void MapSelection(sf::RenderWindow *mapSelectWindow){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        MapSelectActive = false;
        MenuActive = true;
    }
    mapSelectWindow->draw(MapOptionsObj->sprite);
    for (size_t i = getDataJson()["gameplay-status"]["currentmaporder"].asUInt() + 1; i < UkMapObj->ukscales.size(); ++i){
        UkMapObj->sprite.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width * UkMapObj->ukscales[i][0], sf::VideoMode::getDesktopMode().height * UkMapObj->ukscales[i][1]));
        mapSelectWindow->draw(UkMapObj->sprite);
    }
    if (appInFocus(mapSelectWindow)){
        MapSelectMousePos = sf::Mouse::getPosition(*mapSelectWindow);

        if (isMapHover(0, 0) || isMapHover(1, 1) || isMapHover(2, 2) || isMapHover(3, 3) || isMapHover(4, 4) || isMapHover(5, 5)){
            HandCursorObj->sprite.setPosition(static_cast<float>(MapSelectMousePos.x), static_cast<float>(MapSelectMousePos.y));
            mapSelectWindow->draw(HandCursorObj->sprite);
        } else {
            ArrowCursorObj->sprite.setPosition(static_cast<float>(MapSelectMousePos.x), static_cast<float>(MapSelectMousePos.y));
        // ArrowCursorObj->sprite.setPosition((mapSelectResol.x * UkMapObj->ukscales[0][0]) + mapSelectResol.x * 401/1920, (mapSelectResol.y * UkMapObj->ukscales[0][1]) + mapSelectResol.y * 223/1080);
            mapSelectWindow->draw(ArrowCursorObj->sprite);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (!mouseDown){
                if (isMapHover(0, 0)){
                    MenuSelectionEffect->sound.play();
                    currentMapIndex = 0;
                    gotoChosenMap(currentMapIndex);
                }
                else if (isMapHover(1, 1)){
                    MenuSelectionEffect->sound.play();
                    currentMapIndex = 1;
                    gotoChosenMap(currentMapIndex);
                }
                else if (isMapHover(2, 2)){
                    MenuSelectionEffect->sound.play();
                    currentMapIndex = 2;
                    gotoChosenMap(currentMapIndex);
                }
                else if (isMapHover(3, 3)){
                    MenuSelectionEffect->sound.play();
                    currentMapIndex = 3;
                    gotoChosenMap(currentMapIndex);
                }
                else if (isMapHover(4, 4)){
                    MenuSelectionEffect->sound.play();
                    currentMapIndex = 4;
                    gotoChosenMap(currentMapIndex);
                }
                else if (isMapHover(5, 5)){
                    MenuSelectionEffect->sound.play();
                    currentMapIndex = 5;
                    gotoChosenMap(currentMapIndex);
                }
                mouseDown = true;
            } 
        } else
            mouseDown = false;
    }
}