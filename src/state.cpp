#include "state.h"
#include <__bit_reference>  // for __bit_iterator, operator-, operator==, fill
#include <algorithm>        // for find
#include <chrono>           // for duration, operator-, time_point, duration...
#include <iterator>         // for distance

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

bool GameState::isTargetMet() {
    return ducksShot >= rounds[round].target;
}

size_t GameState::getRound() {
    return round;
}

int GameState::getScore() {
    return score;
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

bool GameState::isGameFinished() {
    return round == rounds.size() - 1;
}

bool GameState::performTally() {
    // Find the first false value
    auto firstFalseIt = std::find(duckAuditStates.begin(), duckAuditStates.end(), false);
    
    // If no false value is found, return false
    if (firstFalseIt == duckAuditStates.end()) {
        return false;
    }
    
    // Find the next true value after the first false value
    auto nextTrueIt = std::find(firstFalseIt + 1, duckAuditStates.end(), true);
    
    // If no true value is found, return false
    if (nextTrueIt == duckAuditStates.end()) {
        return false;
    }

    // Calculate the index of the first false value
    size_t firstFalseIndex = static_cast<size_t>(std::distance(duckAuditStates.begin(), firstFalseIt));

    // Shift all elements after the first false one position to the left
    for (size_t i = firstFalseIndex; i < duckAuditStates.size() - 1; ++i) {
        duckAuditStates[i] = duckAuditStates[i + 1];
    }
    
    // Append a false value at the end of the array
    duckAuditStates[duckAuditStates.size() - 1] = false;

    return true;
}
