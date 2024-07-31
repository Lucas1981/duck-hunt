#ifndef GAME_H
#define GAME_H

#include <list>        // for list
#include "animator.h"  // for Animator
#include "clock.h"     // for Clock
#include "graphics.h"  // for Graphics
#include "input.h"     // for Input
#include "screens.h"   // for Screens
#include "state.h"     // for GameState
class Actor;  // lines 12-12
class Play;

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
    Screens screens;
    Animator animator;
    std::list<Actor*> actors;  // Use a list to store agents
    Play* play;
};

#endif // GAME_H
