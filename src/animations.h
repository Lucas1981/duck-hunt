#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <vector>

namespace Animations {
    enum AnimationIndex {
        RED_CROSSHAIRS = 0,
        FLY_HORIZONTAL_RIGHT = 1,
        SHOT = 2,
        FALLING = 3,
        BULLET = 4,
        WHITE_DUCK = 5,
        RED_DUCK = 6,
        FLICKER_DUCK = 7,
        TARGET = 8,
        SCORE = 9,
        FLY_HORIZONTAL_LEFT = 10
    };

    const std::vector<std::vector<int>> animations = {
        {0}, // 0 RED_CROSSHAIRS
        {1, 2}, // 1 FLY_HORIZONTAL_RIGHT
        {3}, // 2 SHOT
        {4, 5}, // 3 FALLING
        {6}, // 4 BULLET
        {7}, // 5 WHITE_DUCK
        {8}, // 6 RED_DUCK,
        {7, 9}, // 7 FLICKER_DUCK
        {10}, // 8 TARGET
        {11}, // 9 SCORE
        {12, 13} // FLY_HORIZONTAL_LEFT
    };
}

#endif // ANIMATIONS_H
