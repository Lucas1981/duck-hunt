#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <vector>

namespace Animations {
    enum AnimationIndex {
        CROSSHAIRS = 0,
        FLY_HORIZONTAL_RIGHT = 1
        // Add other animation indices here
    };

    const std::vector<std::vector<int>> animations = {
        {0}, // CROSSHAIRS
        {1, 2} // FLY_HORIZONTAL_RIGHT
        // Add other animations here
    };
}

#endif // ANIMATIONS_H
