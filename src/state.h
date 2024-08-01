#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "clock.h"

enum class GameStateType {
    TITLE_SCREEN,
    RESET,
    READY,
    RUNNING,
    HIT,
    MISS
};

class GameState {
public:
    GameState(Clock& clock);
    GameStateType getState() const;
    void setState(GameStateType newState);
    double getTimeSinceLastStateChange();
    void reload();
    void decreaseBullets();
    int getBullets();

private:
    static constexpr int NUMBER_OF_ALLOWED_BULLETS = 3;
    int bullets;
    ClockType::time_point lastStateChange;
    GameStateType state;
    Clock& clock;
};

#endif // GAME_STATE_H
