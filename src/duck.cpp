#include "duck.h"
#include <SFML/Graphics/Rect.hpp>  // for FloatRect, Rect::Rect<T>
#include <chrono>                  // for duration, duration_cast, operator-
#include "animations.h"            // for AnimationIndex
#include "animator.h"              // for Animator
#include "constants.h"             // for UNIT_SIZE
#include "sound.h"
namespace sf { class RenderTarget; }

using namespace Constants;

// Define and initialize static members
std::mt19937 Duck::gen(std::random_device{}());
std::uniform_int_distribution<> Duck::directionDistribution(-1, 1);
std::uniform_int_distribution<> Duck::startXDistribution(
    static_cast<int>(UNIT_SIZE), static_cast<int>(SCREEN_WIDTH - UNIT_SIZE)
);

Duck::Duck(
    Animator& _animator,
    Clock& _clock,
    Sound& _sound,
    double _speed
) : clock(_clock),
    animator(_animator),
    sound(_sound),
    speed(_speed)
{
    x = getRandomStartX();
    y = LOWER_BOUND;
    type = AgentType::DUCK;
    state = AgentState::FLYING;
    startTime = clock.getCurrentTime();
    lastDirectionChange = clock.getCurrentTime();
    animationKey = Animations::FLY_HORIZONTAL_RIGHT;
    active = true;
    handleDirectionChange();
    directionY = -1; // Override initial direction so duck goes up
    initializeHitboxes();
    sound.enqueue(SoundEffect::QUACK);
    lastQuack = clock.getCurrentTime();
}

Duck::~Duck() {
    // Handle destruction
}

void Duck::initializeHitboxes() {
    hitboxes[Animations::FLY_HORIZONTAL_RIGHT] = sf::FloatRect(0, 0, UNIT_SIZE, UNIT_SIZE);
    hitboxes[Animations::FLY_HORIZONTAL_LEFT] = sf::FloatRect(0, 0, UNIT_SIZE, UNIT_SIZE);
}

int Duck::getRandomDirection() {
    return directionDistribution(gen);
}

int Duck::getRandomStartX() {
    return startXDistribution(gen);
}

void Duck::update() {
    ClockType::time_point currentTime = clock.getCurrentTime();

    if (state == AgentState::SHOT) {
        handleFallingState(currentTime);
    }

    if (state == AgentState::FLYING) {
        handleFlyingState(currentTime);
    }

    double elapsedTime = clock.getElapsedTime();
    double finalSpeed = state == AgentState::FALLING ? FALLING_SPEED : speed;
    x += finalSpeed * elapsedTime * directionX;
    y += finalSpeed * elapsedTime * directionY;

    if (x < LEFT_BOUND) {
        x = LEFT_BOUND;
        directionX *= -1;
    }
    if (x > RIGHT_BOUND) {
        x = RIGHT_BOUND;
        directionX *= -1;
    }
    double stateBasedUpperBound = state == AgentState::ESCAPING ? 0 : UPPER_BOUND;
    if (y < stateBasedUpperBound) {
        y = stateBasedUpperBound;
        directionY *= -1;
    }
    if (y > LOWER_BOUND) {
        y = LOWER_BOUND;
        directionY *= -1;
    }
}

void Duck::handleFallingState(ClockType::time_point currentTime) {
    if (
        std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - timeShot
        ).count() > TIME_TO_FALL
    ) {
        state = AgentState::FALLING;
        directionY = 1;
        animationKey = Animations::FALLING;
    }
}

void Duck::handleFlyingState(ClockType::time_point currentTime) {
    if (
        std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - lastDirectionChange
        ).count() > TIME_TO_DIRECTION_CHANGE
    ) {
        lastDirectionChange = currentTime;
        handleDirectionChange();
    }

    if (
        std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - lastQuack
        ).count() > TIME_TO_QUACK
    ) {
        lastQuack = currentTime;
        sound.enqueue(SoundEffect::QUACK);
    }
}

void Duck::handleDirectionChange() {
    do {    
        directionX = getRandomDirection();
        directionY = getRandomDirection();
    } while (directionX == 0 && directionY == 0);

    animationKey = directionX == 1 ?
        Animations::FLY_HORIZONTAL_RIGHT :
        Animations::FLY_HORIZONTAL_LEFT;
}

void Duck::draw(sf::RenderTarget& target) {
    ClockType::time_point currentTime = clock.getCurrentTime();
    float elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

    animator.draw(
        target,
        static_cast<float>(x),
        static_cast<float>(y),
        animationKey,
        elapsedTime
    );
}

void Duck::handleShot() {
    timeShot = clock.getCurrentTime();
    state = AgentState::SHOT;
    directionX = 0;
    directionY = 0;
    animationKey = Animations::SHOT;
}

void Duck::handleEscaping() {
    directionX = 0;
    directionY = -1;
    state = AgentState::ESCAPING;
}

sf::FloatRect Duck::getTranslatedHitbox() const {
    sf::FloatRect currentHitbox = hitboxes.at(animationKey);
    currentHitbox.left += static_cast<float>(x);
    currentHitbox.top += static_cast<float>(y);
    return currentHitbox;
}

bool Duck::isFalling() {
    return state == AgentState::FALLING;
}

bool Duck::isUpperThresholdReached() {
    return y == 0;
}

bool Duck::isLowerThresholdReached() {
    return y >= LOWER_BOUND;
}