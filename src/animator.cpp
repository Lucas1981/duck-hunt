#include "animator.h"
#include <stddef.h>  // for size_t
#include <vector>    // for vector
#include "frames.h"  // for Frames
namespace sf { class RenderTarget; }

Animator::Animator(Animations::AnimationIndex initialAnimation)
    : currentAnimation(initialAnimation), currentFrame(0), frameTime(0.1f), elapsedTime(0.0f),
      frames(Frames::getInstance()) {
    // Initial setup
}

void Animator::changeAnimation(Animations::AnimationIndex animationIndex) {
    if (animationIndex != currentAnimation) {
        currentAnimation = animationIndex;
        currentFrame = 0;
        elapsedTime = 0.0f;
    }
}

void Animator::draw(sf::RenderTarget& target, float x, float y) {
    frames.draw(target, x, y, Animations::animations[currentAnimation][(size_t)currentFrame]);
}

void Animator::update(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime) {
        elapsedTime -= frameTime;
        currentFrame++;
        if (currentFrame >= (int)Animations::animations[currentAnimation].size()) {
            currentFrame = 0;
        }
    }
}
