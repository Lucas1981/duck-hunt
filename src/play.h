#ifndef PLAY_H
#define PLAY_H

#include <list>  // for list
class Actor;  // lines 5-5
class Animator;  // lines 6-6
class Clock;  // lines 7-7
class Duck;  // lines 8-8
class GameState;  // lines 9-9
class Graphics;  // lines 10-10
class Input;  // lines 16-16
class Player;  // lines 11-11
class Screens;  // lines 12-12
class Sound;  // lines 15-15
class Text;  // lines 13-13
class UserInterface;  // lines 14-14

class Play {
public:
    Play(
        Graphics& _graphics,
        Screens& _screens,
        std::list<Actor*>& _actors,
        GameState* _gameState,
        Animator& _animator,
        Text& text,
        Clock& _clock,
        Sound& _sound,
        Input& input
    );
    ~Play();
    
    void run(bool handleInput);

private:
    void update();
    void handleActorUpdate(Actor* actor, bool& isStateChanged);
    void inputHandler();
    void handlePlayerShot();
    void handleDuckShot(Duck* duck);
    void removeInactiveActors();
    void draw();
    
    Graphics& graphics;
    Screens& screens;
    std::list<Actor*>& actors;
    GameState* gameState;
    Clock& clock;
    Animator& animator;
    UserInterface* userInterface;
    Sound& sound;
    Player* player;
};

#endif // PLAY_H
