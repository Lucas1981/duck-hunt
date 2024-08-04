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
    void reloadBullets();
    void decreaseBullets();
    void decreaseDucks();
    void increaseDucksShot();
    void increaseRound();
    void resetDucksForRound();
    void startTimeToShoot();
    int getBullets();
    int getDucksLeft();
    int getDucksShot();
    bool isTargetMet();
    bool timeToShootExpired();

private:
    static constexpr int NUMBER_OF_ALLOWED_BULLETS = 3;
    static constexpr int DUCKS_PER_ROUND = 4;
    static constexpr int TOTAL_ROUNDS = 4;
    static constexpr int ALLOWED_SHOOTING_TIME = 8;
    int round;
    int bullets;
    int ducksLeft;
    int ducksShot;
    int target;
    ClockType::time_point lastStateChange;
    ClockType::time_point timeToShoot;
    GameStateType state;
    Clock& clock;
};

#endif // GAME_STATE_H
