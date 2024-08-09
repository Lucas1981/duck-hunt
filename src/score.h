#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics/Rect.hpp>  // for FloatRect
#include "actor.h"                 // for Actor
#include "clock.h"                 // for ClockType
class Animator;
namespace sf { class RenderTarget; }

class Score : public Actor {
public:
    Score(Animator& _animator, Clock& clock, double initialX, double initialY);
    ~Score() override;
    void update() override;
    void draw(sf::RenderTarget& target) override;
    sf::FloatRect getTranslatedHitbox() const override;

private:
    Animator& animator;
    Clock& clock;
    ClockType::time_point spawnTime;
    static constexpr double LIFESPAN = 1; //
    static constexpr double SPEED = 0.01; // Speed of upward movement
};

#endif // SCORE_H
