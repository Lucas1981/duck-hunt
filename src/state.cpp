#include "state.h"

GameState::GameState() : state(GameStateType::RUNNING) {}

GameStateType GameState::getState() const {
    return state;
}

void GameState::setState(GameStateType newState) {
    state = newState;
}