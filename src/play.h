#ifndef PLAY_H
#define PLAY_H

#include <list>  // for list
class Actor;  // lines 11-11
class Graphics;
class Screens;

class Play {
public:
    Play(Graphics& graphics, Screens& screens, std::list<Actor*>& actors);
    void run();

private:
    Graphics& graphics;
    Screens& screens;
    std::list<Actor*>& actors;
};

#endif // PLAY_H
