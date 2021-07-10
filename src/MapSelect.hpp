#pragma once
#include "State.hpp"

class MAPSELECT : public State {
private:
    sf::Texture ukTexture, mapOptionsTexture;
    sf::Sprite ukSprite, mapOptionsSprite;
    sf::Vector2i MapSelectMousePos;
    sf::Vector2f mapSelectResol;
    std::array<std::array<float,2>, 6> ukscales {{{0.2510416667, 0.1962962963},{0.5463541667, 0.1962962963}, {0.2510416667, 0.437037037}, {0.5463541667, 0.437037037}, {0.2510416667, 0.6787037037}, {0.5463541667, 0.6787037037}}};
    bool musicStop;
public:
    MAPSELECT();
    bool isMapHover(const int &jsonMapIndex, size_t ith);
    virtual void run(sf::RenderWindow *window, const float &dtArg) override;
    virtual void loadResources() override;
    virtual void notInStateProcess() override;
};