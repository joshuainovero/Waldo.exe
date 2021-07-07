#include "State.hpp"
#include <Windows.h>
std::vector<State*> State::states;
State *State::currentState;

State::~State(){
    for (size_t i = 0; i < State::states.size(); ++i){
        delete State::states[i];
    }
    State::states.clear();
}