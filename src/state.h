#ifndef GAME_STATE_H
#define GAME_STATE_H

enum class GameStateType {
    TITLE_SCREEN,
    READY,
    RUNNING,
};

class GameState {
public:
    GameState();
    GameStateType getState() const;
    void setState(GameStateType newState);

private:
    GameStateType state;
};

#endif // GAME_STATE_H
