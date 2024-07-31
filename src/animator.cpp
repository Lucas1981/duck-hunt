#include "animator.h"
#include <stddef.h>  // for size_t
#include <vector>    // for vector

Animator::Animator() {}

void Animator::draw(sf::RenderTarget& target, float x, float y, Animations::AnimationIndex animationType, float elapsedTime) {
    const auto& animation = Animations::animations[static_cast<size_t>(animationType)];
    int numberOfFrames = static_cast<int>(animation.size());
    
    // Calculate the frame number
    int frameNumber = static_cast<int>(elapsedTime / 1000.0f * FRAMES_PER_SECOND) % numberOfFrames;
    int frameIndex = animation[static_cast<size_t>(frameNumber)];

    // Draw the frame
    frames.draw(target, x, y, frameIndex);
}
