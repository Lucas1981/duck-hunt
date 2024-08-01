#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "clock.h"

enum class GameStateType {
    TITLE_SCREEN,
    READY,
    RUNNING,
    HIT,
    // MISS
};

class GameState {
public:
    GameState(Clock& clock);
    GameStateType getState() const;
    void setState(GameStateType newState);
    double getTimeSinceLastStateChange();

private:
    ClockType::time_point lastStateChange;
    GameStateType state;
    Clock& clock;
};

#endif // GAME_STATE_H
