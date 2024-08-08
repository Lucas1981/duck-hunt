#include "state.h"
#include <__bit_reference>  // for fill
#include <chrono>           // for duration, operator-, time_point, duration...

GameState::GameState(Clock& _clock) : state(GameStateType::TITLE_SCREEN), clock(_clock)  {
    lastStateChange = clock.getCurrentTime();
    round = 0;
    bullets = NUMBER_OF_ALLOWED_BULLETS;
    ducksLeft = DUCKS_PER_ROUND;
    ducksShot = 0;
    score = 0;
    initializeRounds();
    duckAuditStates = std::vector<bool>(DUCKS_PER_ROUND, false); // Initialize with false
}

GameStateType GameState::getState() const {
    return state;
}

void GameState::initializeRounds() {
    rounds = {
        {300, 6},
        {400, 7},
        {500, 8},
        {600, 9},
        {700, 10},
    };
}

void GameState::resetDuckAuditStates() {
    std::fill(duckAuditStates.begin(), duckAuditStates.end(), false);
}

void GameState::setState(GameStateType newState) {
    state = newState;
    lastStateChange = clock.getCurrentTime();
}

double GameState::getTimeSinceLastStateChange() {
    ClockType::time_point now = clock.getCurrentTime();
    return std::chrono::duration<double>(now - lastStateChange).count();
}

float GameState::getAnimationTime() {
    ClockType::time_point now = clock.getCurrentTime();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - lastStateChange).count();
}

void GameState::reloadBullets() {
    bullets = NUMBER_OF_ALLOWED_BULLETS;
}

void GameState::resetDucksForRound() {
    ducksLeft = DUCKS_PER_ROUND;
    ducksShot = 0;
    resetDuckAuditStates();
}

void GameState::resetGame() {
    resetDucksForRound();
    round = 0;
    score = 0;
}

void GameState::decreaseBullets() {
    bullets--;
}

void GameState::decreaseDucks() {
    ducksLeft--;
}

void GameState::increaseDucksShot() {
    ducksShot++;
    score += SCORE_PER_DUCK;
}

void GameState::markAuditDuckAsShot(size_t index) {
    duckAuditStates[index] = true;
}

void GameState::increaseRound() {
    round++;
}

int GameState::getBullets() {
    return bullets;
}

int GameState::getDucksLeft() {
    return ducksLeft;
}

int GameState::getDucksShot() {
    return ducksShot;
}

bool GameState::isTargetMet() {
    return ducksShot >= rounds[round].target;
}

int GameState::getDucksPerRound() {
    return DUCKS_PER_ROUND;
}

size_t GameState::getRound() {
    return round;
}

int GameState::getScore() {
    return score;
}

double GameState::getTimeToShoot() {
    ClockType::time_point now = clock.getCurrentTime();
    return std::chrono::duration<double>(now - timeToShoot).count();
}

double GameState::getRoundSpeed() {
    return rounds[round].speed;
}

const std::vector<bool>& GameState::getDuckAuditStates() const {
    return duckAuditStates;
}

size_t GameState::getDuckAuditIndex() {
    return static_cast<size_t>(DUCKS_PER_ROUND - ducksLeft);
}

void GameState::startTimeToShoot() {
    timeToShoot = clock.getCurrentTime();
}

bool GameState::timeToShootExpired() {
    ClockType::time_point now = clock.getCurrentTime();
    return std::chrono::duration<double>(now - timeToShoot).count() >= ALLOWED_SHOOTING_TIME;
}

bool GameState::isRoundEnd() {
    return ducksLeft == 0;
}

bool GameState::isRoundBegin() {
    return ducksLeft == DUCKS_PER_ROUND;
}

bool GameState::isGameFinished() {
    return round == rounds.size() - 1;
}
