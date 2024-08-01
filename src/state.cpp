#include "state.h"
#include <chrono>  // for duration, operator-, time_point

GameState::GameState(Clock& _clock) : state(GameStateType::RUNNING), clock(_clock)  {
    lastStateChange = clock.getCurrentTime();
    bullets = NUMBER_OF_ALLOWED_BULLETS;
}

GameStateType GameState::getState() const {
    return state;
}

void GameState::setState(GameStateType newState) {
    state = newState;
    lastStateChange = clock.getCurrentTime();
}

double GameState::getTimeSinceLastStateChange() {
    ClockType::time_point now = clock.getCurrentTime();
    return std::chrono::duration<double>(now - lastStateChange).count();
}

void GameState::reload() {
    bullets = NUMBER_OF_ALLOWED_BULLETS;
}

void GameState::decreaseBullets() {
    bullets--;
}

int GameState::getBullets() {
    return bullets;
}