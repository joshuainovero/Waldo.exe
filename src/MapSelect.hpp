#pragma once

class MAPSELECT : public State {
private:
    sf::Texture ukTexture, mapOptionsTexture;
    sf::Sprite ukSprite, mapOptionsSprite;
    sf::Vector2i MapSelectMousePos;
    sf::Vector2f mapSelectResol;

    std::array<std::array<float,2>, 6> ukscales {{{0.2510416667, 0.1962962963},{0.5463541667, 0.1962962963}, {0.2510416667, 0.437037037}, {0.5463541667, 0.437037037}, {0.2510416667, 0.6787037037}, {0.5463541667, 0.6787037037}}};
public:
    MAPSELECT();
    bool isMapHover(const int &jsonMapIndex, size_t ith);
    virtual void run(sf::RenderWindow *window, const float &dtArg) override;
    virtual void loadResources() override;
};

void MAPSELECT::loadResources(){
    mapSelectResol.x = sf::VideoMode::getDesktopMode().width;
    mapSelectResol.y = sf::VideoMode::getDesktopMode().height;

    //* UNKNOWN ICONS */
    createSprite(ukTexture, ukSprite, "Assets/004/004-uk");
    ukSprite.setScale(sf::Vector2f(State::getFullScreenSpriteScale(), State::getFullScreenSpriteScale()));

    /* MAP OPTIONS */
    createSprite(mapOptionsTexture, mapOptionsSprite, "Assets/004/004-mo");
    mapOptionsSprite.setScale(sf::Vector2f(State::getFullScreenSpriteScale(), State::getFullScreenSpriteScale()));
}

MAPSELECT::MAPSELECT(){ loadResources(); }

bool MAPSELECT::isMapHover(const int &jsonMapIndex, size_t ith){
    return ((MapSelectMousePos.x >= mapSelectResol.x*ukscales[ith][0] && MapSelectMousePos.x <= (mapSelectResol.x * ukscales[ith][0]) + mapSelectResol.x * 401/1920) &&
        (MapSelectMousePos.y >= mapSelectResol.y*ukscales[ith][1] && MapSelectMousePos.y <= (mapSelectResol.y * ukscales[ith][1]) + mapSelectResol.y * 223/1080))
        && getDataJson()["gameplay-status"]["inGameMaps"][jsonMapIndex]["mapStatus"].asBool();
}


void MAPSELECT::run(sf::RenderWindow *window, const float &dtArg){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        currentState = states.at(0);
    }
    window->draw(mapOptionsSprite);
    for (size_t i = getDataJson()["gameplay-status"]["currentmaporder"].asUInt() + 1; i < ukscales.size(); ++i){
        ukSprite.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width * ukscales[i][0], sf::VideoMode::getDesktopMode().height * ukscales[i][1]));
        window->draw(ukSprite);
    }
    if (Engine::appInFocus(window)){
        MapSelectMousePos = sf::Mouse::getPosition(*window);

        if (isMapHover(0, 0) || isMapHover(1, 1) || isMapHover(2, 2) || isMapHover(3, 3) || isMapHover(4, 4) || isMapHover(5, 5)){
            State::handSprite.setPosition(static_cast<float>(MapSelectMousePos.x), static_cast<float>(MapSelectMousePos.y));
            window->draw(State::handSprite);
        } else {
            State::arrowSprite.setPosition(static_cast<float>(MapSelectMousePos.x), static_cast<float>(MapSelectMousePos.y));
        // ArrowCursorObj->sprite.setPosition((mapSelectResol.x * UkMapObj->ukscales[0][0]) + mapSelectResol.x * 401/1920, (mapSelectResol.y * UkMapObj->ukscales[0][1]) + mapSelectResol.y * 223/1080);
            window->draw(State::arrowSprite);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (!Engine::mouseDown){
                if (isMapHover(0, 0)){
                    globalClickSound.play();
                    INGAME::currentMapIndex = 0;
                    INGAME::gotoChosenMap(INGAME::currentMapIndex);
                }
                else if (isMapHover(1, 1)){
                    globalClickSound.play();
                    INGAME::currentMapIndex = 1;
                    INGAME::gotoChosenMap(INGAME::currentMapIndex);
                }
                else if (isMapHover(2, 2)){
                    globalClickSound.play();
                    INGAME::currentMapIndex = 2;
                    INGAME::gotoChosenMap(INGAME::currentMapIndex);
                }
                else if (isMapHover(3, 3)){
                    globalClickSound.play();
                    INGAME::currentMapIndex = 3;
                    INGAME::gotoChosenMap(INGAME::currentMapIndex);
                }
                else if (isMapHover(4, 4)){
                    globalClickSound.play();
                    INGAME::currentMapIndex = 4;
                    INGAME::gotoChosenMap(INGAME::currentMapIndex);
                }
                else if (isMapHover(5, 5)){
                    globalClickSound.play();
                    INGAME::currentMapIndex = 5;
                    INGAME::gotoChosenMap(INGAME::currentMapIndex);
                }
                Engine::mouseDown = true;
            } 
        } else
            Engine::mouseDown = false;
    }   
}
