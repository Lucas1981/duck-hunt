#include "duck.h"
#include <SFML/Graphics/Rect.hpp>  // for FloatRect, Rect::Rect<T>
#include <chrono>                  // for duration, duration_cast, operator-
#include "animations.h"            // for AnimationIndex
#include "animator.h"              // for Animator
#include "constants.h"             // for UNIT_SIZE
namespace sf { class RenderTarget; }

using namespace Constants;

// Define and initialize static members
std::mt19937 Duck::gen(std::random_device{}());
std::uniform_int_distribution<> Duck::directionDistribution(-1, 1);
std::uniform_int_distribution<> Duck::startXDistribution(
    static_cast<int>(UNIT_SIZE), static_cast<int>(SCREEN_WIDTH - UNIT_SIZE)
);

Duck::Duck(Animator& _animator, Clock& _clock) : clock(_clock), animator(_animator) {
    x = getRandomStartX();
    y = LOWER_BOUND;
    type = AgentType::DUCK;
    state = AgentState::FLYING;
    startTime = clock.getCurrentTime();
    lastDirectionChange = clock.getCurrentTime();
    animationKey = Animations::FLY_HORIZONTAL_RIGHT;
    handleDirectionChange();
    initializeHitboxes();
}

Duck::~Duck() {
    // Handle destruction
}

void Duck::initializeHitboxes() {
    hitboxes[Animations::FLY_HORIZONTAL_RIGHT] = sf::FloatRect(0, 0, UNIT_SIZE, UNIT_SIZE);
    // Add other hitboxes as needed
}

int Duck::getRandomDirection() {
    return directionDistribution(gen);
}

int Duck::getRandomStartX() {
    return startXDistribution(gen);
}

void Duck::update() {
    if (
        state == AgentState::FLYING &&
        std::chrono::duration_cast<std::chrono::milliseconds>(
            clock.getCurrentTime() - lastDirectionChange
        ).count() > timeToDirectionChange
    ) {
        lastDirectionChange = clock.getCurrentTime();
        handleDirectionChange();
    }

    double elapsedTime = clock.getElapsedTime();

    x += speed * elapsedTime * directionX;
    y += speed * elapsedTime * directionY;

    if (x < LEFT_BOUND) {
        x = LEFT_BOUND;
        directionX *= -1;
    }
    if (x > RIGHT_BOUND) {
        x = RIGHT_BOUND;
        directionX *= -1;
    }
    double stateBasedUpperBound = state == AgentState::ESCAPED ? 0 : UPPER_BOUND;
    if (y < stateBasedUpperBound) {
        y = stateBasedUpperBound;
        directionY *= -1;
    }
    if (y > LOWER_BOUND) {
        y = LOWER_BOUND;
        directionY *= -1;
    }
}

void Duck::handleDirectionChange() {
    do {    
        directionX = getRandomDirection();
        directionY = getRandomDirection();
    } while(directionX == 0 && directionY == 0);
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
    state = AgentState::SHOT;
    directionX = 0;
    directionY = 0;
    animationKey = Animations::SHOT;
}

void Duck::handleEscaped() {
    directionX = 0;
    directionY = -1;
    state = AgentState::ESCAPED;
}

sf::FloatRect Duck::getTranslatedHitbox() const {
    sf::FloatRect currentHitbox = hitboxes.at(animationKey);
    currentHitbox.left += static_cast<float>(x);
    currentHitbox.top += static_cast<float>(y);
    return currentHitbox;
}