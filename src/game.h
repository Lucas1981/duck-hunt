#ifndef GAME_H
#define GAME_H

#include "clock.h"     // for Clock
#include "graphics.h"  // for Graphics
#include "input.h"     // for Input
#include "screens.h"   // for Screens
class GameState;  // lines 14-14
class StateHandlers;

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    bool initialize();
    void cleanup();
    void resetActors();

    GameState* gameState;
    Input input;
    Graphics graphics;
    Clock clock;
    Screens screens;
    StateHandlers* stateHandlers;
};

#endif // GAME_H
