#ifndef ENGINE_H
#define ENGINE_H

#include "GameResources.hpp"

class Engine {
private:
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    GameResources resources;
    unsigned int framerateLimit;
    float dt;

    #ifdef DEBUG
    uint32_t appWidth, appHeight;
    float tt;
    void debugManager();
    #endif // DEBUG
    
private:
    void getMainDirectory();
    void updateDeltaTime();
    void updateSFMLEvents();
    void update();
    void render();

public:
    Engine();
    ~Engine();
    void run();
};

#endif // ENGINE_H