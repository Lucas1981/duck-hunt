#ifndef HANDLERS_H
#define HANDLERS_H

#include <list>        // for list
#include <string>      // for string
#include "animator.h"  // for Animator
#include "text.h"      // for Text
class Actor;
class Clock;
class GameState;
class Graphics;
class Input;
class Play;
class Screens;
class Sound;

class StateHandlers {
public:
    StateHandlers(
        GameState* _gameState,
        Input& _input,
        Screens& _screens,
        Graphics& _graphics,
        Clock& _clock,
        Sound& sound
    );
    ~StateHandlers();
    void handleTitleScreenState();
    void handleReadyState();
    void handleRunningState();
    void handleHitState();
    void handleMissState();
    void handleFlownState();
    void handleTallyState();
    void handleHoldState();
    void handleResetState();
    void handleRoundBeginState();
    void handleRoundWonState();
    void handleGameOverState();
    void handleFinishedState();

private:
    static constexpr int VERTICAL_ANCHOR = 300;
    void drawText(const std::string& str);
    void drawText(float x, float y, const std::string& str);
    void resetActors();
    void setupRoundBegin();
    void setupTitleScreen();
    GameState* gameState;
    Input& input;
    Screens& screens;
    Graphics& graphics;
    Clock& clock;
    Text text;
    Play* play;
    std::list<Actor*> actors;  // Use a list to store agents
    Animator animator;
    Sound& sound;
};

#endif