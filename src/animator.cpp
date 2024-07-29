#include "animator.h"
#include <stddef.h>  // for size_t
#include <vector>    // for vector

Animator::Animator() {}

void Animator::draw(sf::RenderTarget& target, float x, float y, Animations::AnimationIndex animationType, float elapsedTime) {
    const auto& animation = Animations::animations[(size_t)animationType];
    int numberOfFrames = (int)animation.size();
    int frameNumber = static_cast<int>((elapsedTime * FRAMES_PER_SECOND / 1000.0f)) % numberOfFrames;
    int frameIndex = animation[(size_t)frameNumber];

    frames.draw(target, x, y, frameIndex);
}
