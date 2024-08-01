#ifndef GAME_H
#define GAME_H

#include <list>        // for list
#include "animator.h"  // for Animator
#include "clock.h"     // for Clock
#include "graphics.h"  // for Graphics
#include "input.h"     // for Input
#include "screens.h"   // for Screens
class Actor;  // lines 11-11
class GameState;
class Play;  // lines 12-12

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void handleReadyState();
    void handleRunningState();
    void handleHitState();
    bool initialize();
    void cleanup();
    void reset();

    GameState* gameState;
    Input input;
    Graphics graphics;
    Clock clock;
    Screens screens;
    Animator animator;
    std::list<Actor*> actors;  // Use a list to store agents
    Play* play;
};

#endif // GAME_H
