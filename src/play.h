#ifndef PLAY_H
#define PLAY_H

#include <list>  // for list
class Actor;  // lines 7-7
class Animator;
class GameState;  // lines 8-8
class Graphics;  // lines 9-9
class Screens;  // lines 10-10
class UserInterface;
class Text;
class Clock;

class Play {
public:
    Play(
        Graphics& _graphics,
        Screens& _screens,
        std::list<Actor*>& _actors,
        GameState* _gameState,
        Animator& _animator,
        Text& text,
        Clock& clock
    );
    ~Play();
    void run(bool handleInput);
    
private:
    void update();
    void inputHandler();
    void draw();
    void removeInactiveActors();
    Animator& animator;
    Graphics& graphics;
    Screens& screens;
    GameState* gameState;
    std::list<Actor*>& actors;
    UserInterface* userInterface;
    Clock& clock;
};

#endif // PLAY_H
