#pragma once

class MAPSELECT : public State {
private:
    sf::Vector2i MapSelectMousePos;
    sf::Vector2f mapSelectResol;
public:
    MAPSELECT(){
        mapSelectResol.x = sf::VideoMode::getDesktopMode().width;
        mapSelectResol.y = sf::VideoMode::getDesktopMode().height;
    }
    bool isMapHover(const int &jsonMapIndex, size_t ith){
    return ((MapSelectMousePos.x >= mapSelectResol.x*UkMapObj->ukscales[ith][0] && MapSelectMousePos.x <= (mapSelectResol.x * UkMapObj->ukscales[ith][0]) + mapSelectResol.x * 401/1920) &&
        (MapSelectMousePos.y >= mapSelectResol.y*UkMapObj->ukscales[ith][1] && MapSelectMousePos.y <= (mapSelectResol.y * UkMapObj->ukscales[ith][1]) + mapSelectResol.y * 223/1080))
        && getDataJson()["gameplay-status"]["inGameMaps"][jsonMapIndex]["mapStatus"].asBool();
}
    virtual void run(sf::RenderWindow *window, const float &dtArg) override {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        currentState = states.at(0);
    }
    window->draw(MapOptionsObj->sprite);
    for (size_t i = getDataJson()["gameplay-status"]["currentmaporder"].asUInt() + 1; i < UkMapObj->ukscales.size(); ++i){
        UkMapObj->sprite.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width * UkMapObj->ukscales[i][0], sf::VideoMode::getDesktopMode().height * UkMapObj->ukscales[i][1]));
        window->draw(UkMapObj->sprite);
    }
    if (appInFocus(window)){
        MapSelectMousePos = sf::Mouse::getPosition(*window);

        if (isMapHover(0, 0) || isMapHover(1, 1) || isMapHover(2, 2) || isMapHover(3, 3) || isMapHover(4, 4) || isMapHover(5, 5)){
            HandCursorObj->sprite.setPosition(static_cast<float>(MapSelectMousePos.x), static_cast<float>(MapSelectMousePos.y));
            window->draw(HandCursorObj->sprite);
        } else {
            ArrowCursorObj->sprite.setPosition(static_cast<float>(MapSelectMousePos.x), static_cast<float>(MapSelectMousePos.y));
        // ArrowCursorObj->sprite.setPosition((mapSelectResol.x * UkMapObj->ukscales[0][0]) + mapSelectResol.x * 401/1920, (mapSelectResol.y * UkMapObj->ukscales[0][1]) + mapSelectResol.y * 223/1080);
            window->draw(ArrowCursorObj->sprite);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (!Engine::mouseDown){
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
                Engine::mouseDown = true;
            } 
        } else
            Engine::mouseDown = false;
    }   
    }
};
