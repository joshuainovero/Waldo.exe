#ifndef ENGINE_H
#define ENGINE_H

#include "State.hpp"
#include "MapProperties.hpp"
class Engine {
private:
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    void initWindow();

public:
    Engine();
    ~Engine();
    float dt;
    static bool mouseDown;
    void updateDeltaTime();
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};

#endif // ENGINE_H