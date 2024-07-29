#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "animations.h"  // for AnimationIndex
#include "frames.h"      // for Frames
namespace sf { class RenderTarget; }

class Animator {
public:
    static constexpr int FRAMES_PER_SECOND = 10;  // Set the frames per second

    Animator();
    void draw(sf::RenderTarget& target, float x, float y, Animations::AnimationIndex animationType, float elapsedTime);

private:
    Frames frames;  // Frames instance
};

#endif // ANIMATOR_H
