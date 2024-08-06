#ifndef GAME_H
#define GAME_H

#include <list>        // for list
#include <string>      // for string
#include "animator.h"  // for Animator
#include "clock.h"     // for Clock
#include "graphics.h"  // for Graphics
#include "input.h"     // for Input
#include "screens.h"   // for Screens
#include "text.h"      // for Text
class Actor;  // lines 13-13
class GameState;  // lines 14-14
class Play;  // lines 15-15

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void handleTitleScreenState();
    void handleReadyState();
    void handleRunningState();
    void handleHitState();
    void handleMissState();
    void handleFlownState();
    void handleResetState();
    void handleRoundBeginState();
    void handleRoundWonState();
    void handleGameOverState();
    void handleFinishedState();
    bool initialize();
    void cleanup();
    void resetActors();
    void drawText(const std::string& str);

    static constexpr int VERTICAL_ANCHOR = 300;
    GameState* gameState;
    Input input;
    Graphics graphics;
    Clock clock;
    Screens screens;
    Animator animator;
    std::list<Actor*> actors;  // Use a list to store agents
    Play* play;
    Text text;
};

#endif // GAME_H
