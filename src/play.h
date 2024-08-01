#ifndef PLAY_H
#define PLAY_H

#include <list>  // for list
class Actor;  // lines 6-6
class GameState;
class Graphics;  // lines 7-7
class Screens;  // lines 8-8

class Play {
public:
    Play(
        Graphics& graphics,
        Screens& screens,
        std::list<Actor*>& actors,
        GameState* gameState
    );
    void run(bool handleInput);

private:
    void update();
    void inputHandler();
    void draw();
    Graphics& graphics;
    Screens& screens;
    GameState* gameState;
    std::list<Actor*>& actors;
};

#endif // PLAY_H
