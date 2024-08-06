#ifndef DUCK_H
#define DUCK_H

#include "actor.h"      // for Actor
#include "clock.h"      // for ClockType
#include "constants.h"  // for UNIT_SIZE, SCREEN_HEIGHT, SCREEN_WIDTH
#include <unordered_map>
#include <SFML/Graphics/Rect.hpp>  // for FloatRect
#include "animations.h"
#include <random>   // for mt19937, uniform_int_distribution
class Animator;
namespace sf { class RenderTarget; }

using namespace Constants;

class Duck : public Actor {
public:
    Duck(Animator& _animator, Clock& clock);
    ~Duck();
    void update() override;
    void draw(sf::RenderTarget& target) override;
    sf::FloatRect getTranslatedHitbox() const override;
    Animations::AnimationIndex animationKey;
    void handleShot();
    void handleEscaping();
    void handleEscaped();
    void handleFalling();
    bool isEscaped();
    bool isFalling();
    bool isUpperThresholdReached();
    bool isLowerThresholdReached();

private:
    static constexpr double LEFT_BOUND = UNIT_SIZE / 2;
    static constexpr double RIGHT_BOUND = SCREEN_WIDTH + (UNIT_SIZE / 2);
    static constexpr double UPPER_BOUND = UNIT_SIZE / 2;
    static constexpr double LOWER_BOUND = SCREEN_HEIGHT * 0.8;
    static constexpr double TIME_TO_DIRECTION_CHANGE = 500;
    static constexpr double TIME_TO_FALL = 500;
    static constexpr double MOVING_SPEED = 400;
    static constexpr double FALLING_SPEED = 300;

    ClockType::time_point startTime;
    ClockType::time_point lastDirectionChange;
    ClockType::time_point timeShot;
    Clock& clock;
    Animator& animator;
    int directionX;
    int directionY;
    static std::mt19937 gen; // Random number generator
    static std::uniform_int_distribution<> directionDistribution; // Distribution for x coordinate
    static std::uniform_int_distribution<> startXDistribution; // Distribution for x coordinate
    int getRandomDirection();
    int getRandomStartX();

    std::unordered_map<Animations::AnimationIndex, sf::FloatRect> hitboxes;
    void initializeHitboxes();
    void handleDirectionChange();
};

#endif // DUCK_H
