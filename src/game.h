#ifndef GAME_H
#define GAME_H

#include "clock.h"     // for Clock
#include "graphics.h"  // for Graphics
#include "input.h"     // for Input
#include "state.h"     // for GameState
#include "screens.h"
#include "animator.h"
class Player;

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void handleReadyState();
    void handleRunningState();
    bool initialize();
    void cleanup();

    GameState gameState;
    Input input;
    Graphics graphics;
    Clock clock;
    Player* player;
    Screens screens;
    Animator animator;
};

#endif // GAME_H
