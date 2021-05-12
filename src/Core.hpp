#ifndef CORE
#define CORE

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

#include "Filemanip.hpp"
#include "Scales.hpp"
#include "Labels.hpp"
#include "MapProperties.hpp"
#include "loadAssets.hpp"
#include "GameStates.hpp"
#include "GameMenu.hpp"
#include "InGame.hpp"

#endif //CORE