#ifndef PLAY_H
#define PLAY_H

#include <list>  // for list
class Actor;  // lines 7-7
class Animator;
class GameState;  // lines 8-8
class Graphics;  // lines 9-9
class Screens;  // lines 10-10
class UserInterface;

class Play {
public:
    Play(
        Graphics& graphics,
        Screens& screens,
        std::list<Actor*>& actors,
        GameState* gameState,
        Animator& animator
    );
    ~Play();
    void run(bool handleInput);

private:
    void update();
    void inputHandler();
    void draw();
    Graphics& graphics;
    Screens& screens;
    GameState* gameState;
    std::list<Actor*>& actors;
    UserInterface* userInterface;
};

#endif // PLAY_H
