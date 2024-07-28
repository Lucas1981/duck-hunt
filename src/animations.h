#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <vector>

namespace Animations {
    enum AnimationIndex {
        CROSSHAIRS = 0,
        // Add other animation indices here
    };

    const std::vector<std::vector<int>> animations = {
        {0}, // CROSSHAIRS
        // Add other animations here
    };
}

#endif // ANIMATIONS_H
