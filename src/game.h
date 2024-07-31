#ifndef GAME_H
#define GAME_H

#include <list>        // for list
#include "animator.h"  // for Animator
#include "clock.h"     // for Clock
#include "graphics.h"  // for Graphics
#include "input.h"     // for Input
#include "screens.h"   // for Screens
#include "state.h"     // for GameState
class Actor;
class Player;  // lines 12-12

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
    std::list<Actor*> actors;  // Use a list to store agents
};

#endif // GAME_H
