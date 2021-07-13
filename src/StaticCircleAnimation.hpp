#include "StaticObjAnimation.hpp"

class StaticCircleAnimation : public StaticObjAnimation{
private:
    bool shrink;
public:
    StaticCircleAnimation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
    StaticCircleAnimation() {}
    ~StaticCircleAnimation() = default;
    virtual void Update(int row, float deltaTime) override;
};