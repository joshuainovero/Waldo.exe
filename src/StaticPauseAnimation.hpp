#include "StaticObjAnimation.hpp"

class StaticPauseAnimation : public StaticObjAnimation {
public:
    StaticPauseAnimation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
    StaticPauseAnimation() {}
    ~StaticPauseAnimation() = default;
    void resetState();
    bool isStop;
    virtual void Update(int row, float deltaTime) override;
};