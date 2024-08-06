#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <vector>

namespace Animations {
    enum AnimationIndex {
        CROSSHAIRS = 0,
        FLY_HORIZONTAL_RIGHT = 1,
        SHOT = 2,
        FALLING = 3,
        BULLET = 4,
        WHITE_DUCK = 5,
        RED_DUCK = 6
        // Add other animation indices here
    };

    const std::vector<std::vector<int>> animations = {
        {0}, // 0 CROSSHAIRS
        {1, 2}, // 1 FLY_HORIZONTAL_RIGHT
        {3}, // 2 SHOT
        {4, 5}, // 3 FALLING
        {6}, // 4 Bullet
        {7}, // 5 White duck
        {8} // 6 Red duck
        // Add other animations here
    };
}

#endif // ANIMATIONS_H
