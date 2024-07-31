#ifndef DUCK_H
#define DUCK_H

#include "actor.h"      // for Actor
#include "clock.h"      // for ClockType
#include "constants.h"  // for UNIT_SIZE, SCREEN_HEIGHT, SCREEN_WIDTH
class Animator;
namespace sf { class RenderTarget; }

using namespace Constants;

class Duck : public Actor {
public:
    Duck(Animator& _animator, Clock& clock);
    ~Duck();
    void update() override;
    void draw(sf::RenderTarget& target) override;

private:
    static constexpr double LEFT_BOUND = UNIT_SIZE / 2;
    static constexpr double RIGHT_BOUND = SCREEN_WIDTH + (UNIT_SIZE / 2);
    static constexpr double UPPER_BOUND = UNIT_SIZE / 2;
    static constexpr double LOWER_BOUND = SCREEN_HEIGHT + (UNIT_SIZE / 2);
    static constexpr double speed = 250;
    ClockType::time_point startTime;
    Clock& clock;
    Animator& animator;
};

#endif // DUCK_H
