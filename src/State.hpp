#pragma once
#include <SFML/Graphics.hpp>

class State{
public:
    static std::vector<State*> states;
    static State *currentState;
    State() = default;
    virtual ~State();
    virtual void run(sf::RenderWindow *window, const float &dtArg) = 0;
};
