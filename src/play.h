#ifndef PLAY_H
#define PLAY_H

#include <list>  // for list
class Actor;
class Animator;
class Clock;
class Duck;
class GameState;
class Graphics;
class Player;
class Screens;
class Text;
class UserInterface;
class Sound;

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
        Sound& _sound
    );
    ~Play();
    
    void run(bool handleInput);

private:
    void update();
    void handleActorUpdate(Actor* actor, bool& isStateChanged);
    void inputHandler();
    Player* findPlayer();
    void handlePlayerShot(Player* player);
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
};

#endif // PLAY_H
