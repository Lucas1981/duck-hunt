#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"     // for Actor
#include "animator.h"  // for Animator
#include "constants.h"
class Clock;  // lines 6-6
class Input;  // lines 7-7
namespace sf { class RenderTarget; }

using namespace Constants;
class Player : public Actor {
public:
    Player(Input& input, Clock& clock);
    void update() override;
    void draw(sf::RenderTarget& target) override;

private:
    static constexpr double LEFT_BOUND = UNIT_SIZE / 2;
    static constexpr double RIGHT_BOUND = SCREEN_WIDTH + (UNIT_SIZE / 2);
    static constexpr double UPPER_BOUND = UNIT_SIZE / 2;
    static constexpr double LOWER_BOUND = SCREEN_HEIGHT + (UNIT_SIZE / 2);
    static constexpr double speed = 250;
    Input& input;
    Clock& clock;
    Animator animator;
};

#endif // PLAYER_H