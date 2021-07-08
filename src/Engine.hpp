#ifndef ENGINE_H
#define ENGINE_H

#include "State.hpp"
class Engine {
private:
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    void initWindow();
    #ifdef DEBUG
    float tt;
    #endif // DEBUG

public:
    Engine();
    ~Engine();
    float dt;
    static bool mouseDown;
    static bool appInFocus(sf::RenderWindow* app);
    void updateDeltaTime();
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};

#endif // ENGINE_H