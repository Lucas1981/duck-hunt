#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "animations.h"  // for AnimationIndex
class Frames;
namespace sf { class RenderTarget; }

class Animator {
public:
    Animator(Animations::AnimationIndex initialAnimation);
    void changeAnimation(Animations::AnimationIndex animationIndex);
    void draw(sf::RenderTarget& target, float x, float y);
    void update(float deltaTime);

private:
    Animations::AnimationIndex currentAnimation;
    int currentFrame;
    float frameTime;
    float elapsedTime;
    Frames& frames;
};

#endif // ANIMATOR_H
