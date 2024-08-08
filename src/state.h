#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stddef.h>  // for size_t
#include <vector>    // for vector
#include "clock.h"   // for ClockType

enum class GameStateType {
    TITLE_SCREEN,
    RESET,
    ROUND_BEGIN,
    READY,
    RUNNING,
    HIT,
    MISS,
    FLOWN,
    TALLY,
    HOLD,
    GAME_OVER,
    ROUND_WON,
    FINISHED
};

struct Round {
    double speed;
    int target;
};

class GameState {
public:
    GameState(Clock& clock);
    GameStateType getState() const;
    void setState(GameStateType newState);
    double getTimeSinceLastStateChange();
    float getAnimationTime();
    void reloadBullets();
    void decreaseBullets();
    void decreaseDucks();
    void increaseDucksShot();
    void increaseRound();
    void resetDucksForRound();
    void startTimeToShoot();
    void resetGame();
    void markAuditDuckAsShot(size_t index);
    int getBullets();
    size_t getRound();
    int getScore();
    int getTarget();
    double getRoundSpeed();
    size_t getDuckAuditIndex();
    bool isTargetMet();
    bool timeToShootExpired();
    bool isRoundEnd();
    bool isGameFinished();
    bool performTally();
    
    const std::vector<bool>& getDuckAuditStates() const;

private:
    void initializeRounds();
    void resetDuckAuditStates();

    static constexpr int NUMBER_OF_ALLOWED_BULLETS = 3;
    static constexpr int DUCKS_PER_ROUND = 10;
    static constexpr int ALLOWED_SHOOTING_TIME = 6;
    static constexpr int SCORE_PER_DUCK = 100;
    size_t round;
    int bullets;
    int ducksLeft;
    int ducksShot;
    int score;
    std::vector<Round> rounds;
    ClockType::time_point lastStateChange;
    ClockType::time_point timeToShoot;
    GameStateType state;
    Clock& clock;
    std::vector<bool> duckAuditStates;
};

#endif // GAME_STATE_H
