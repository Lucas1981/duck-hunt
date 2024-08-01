#include "state.h"
#include <chrono>  // for duration, operator-, time_point

GameState::GameState(Clock& _clock) : state(GameStateType::RUNNING), clock(_clock)  {
    lastStateChange = clock.getCurrentTime();
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