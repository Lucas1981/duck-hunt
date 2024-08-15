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
class Sound;
namespace sf { class RenderTarget; }

using namespace Constants;

class Duck : public Actor {
public:
    Duck(Animator& _animator, Clock& clock, Sound& _sound, double _speed);
    ~Duck();
    void update() override;
    void draw(sf::RenderTarget& target) override;
    sf::FloatRect getTranslatedHitbox() const override;
    Animations::AnimationIndex animationKey;
    void handleShot();
    void handleEscaping();
    bool isFalling();
    bool isUpperThresholdReached();
    bool isLowerThresholdReached();

private:
    void handleFlyingState(ClockType::time_point currentTime);
    void handleFallingState(ClockType::time_point currentTime);

    static constexpr double LEFT_BOUND = UNIT_SIZE / 2;
    static constexpr double RIGHT_BOUND = SCREEN_WIDTH + (UNIT_SIZE / 2);
    static constexpr double UPPER_BOUND = UNIT_SIZE / 2;
    static constexpr double LOWER_BOUND = 580;
    static constexpr double TIME_TO_DIRECTION_CHANGE = 600;
    static constexpr double TIME_TO_FALL = 500;
    static constexpr double FALLING_SPEED = 300;
    static constexpr double TIME_TO_QUACK = 800;

    ClockType::time_point startTime;
    ClockType::time_point lastDirectionChange;
    ClockType::time_point timeShot;
    ClockType::time_point lastQuack;
    Clock& clock;
    Animator& animator;
    Sound& sound;
    int directionX;
    int directionY;
    static std::mt19937 gen; // Random number generator
    static std::uniform_int_distribution<> directionDistribution; // Distribution for x coordinate
    static std::uniform_int_distribution<> startXDistribution; // Distribution for x coordinate
    int getRandomDirection();
    int getRandomStartX();
    double speed;

    std::unordered_map<Animations::AnimationIndex, sf::FloatRect> hitboxes;
    void initializeHitboxes();
    void handleDirectionChange();
};

#endif // DUCK_H
