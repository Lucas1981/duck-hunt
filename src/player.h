#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"      // for Actor
#include "constants.h"  // for UNIT_SIZE, SCREEN_HEIGHT, SCREEN_WIDTH
class Animator;
class Input;  // lines 9-9
namespace sf { class RenderTarget; }  // lines 10-10

using namespace Constants;
class Player : public Actor {
public:
    Player(Input& input, Animator& animator);
    void update() override;
    void draw(sf::RenderTarget& target) override;

private:
    static constexpr double LEFT_BOUND = UNIT_SIZE / 2;
    static constexpr double RIGHT_BOUND = SCREEN_WIDTH + (UNIT_SIZE / 2);
    static constexpr double UPPER_BOUND = UNIT_SIZE / 2;
    static constexpr double LOWER_BOUND = SCREEN_HEIGHT + (UNIT_SIZE / 2);
    static constexpr double speed = 250;
    Input& input;
    Animator& animator;
};

#endif // PLAYER_H