#include "duck.h"
#include <SFML/Graphics/Rect.hpp>  // for FloatRect, Rect::Rect<T>
#include <chrono>                  // for duration, duration_cast, operator-
#include "animations.h"            // for AnimationIndex
#include "animator.h"              // for Animator
#include "constants.h"             // for UNIT_SIZE
namespace sf { class RenderTarget; }

using namespace Constants;

Duck::Duck(Animator& _animator, Clock& _clock) : clock(_clock), animator(_animator) {
    x = 400.0;
    y = 300.0;
    type = AgentType::DUCK;
    state = AgentState::IDLE;
    startTime = clock.getCurrentTime();
    animationKey = Animations::FLY_HORIZONTAL_RIGHT;
    initializeHitboxes();
}

Duck::~Duck() {
    // Handle destruction
}

void Duck::initializeHitboxes() {
    hitboxes[Animations::FLY_HORIZONTAL_RIGHT] = sf::FloatRect(0, 0, UNIT_SIZE, UNIT_SIZE);
    // Add other hitboxes as needed
}

void Duck::update() {
    // Do later
}

void Duck::draw(sf::RenderTarget& target) {
    auto currentTime = clock.getCurrentTime();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

    animator.draw(
        target,
        static_cast<float>(x),
        static_cast<float>(y),
        animationKey,
        static_cast<float>(elapsedTime)
    );
}

void Duck::handleShot() {
    animationKey = Animations::SHOT;
}

sf::FloatRect Duck::getTranslatedHitbox() const {
    sf::FloatRect currentHitbox = hitboxes.at(animationKey);
    currentHitbox.left += static_cast<float>(x);
    currentHitbox.top += static_cast<float>(y);
    return currentHitbox;
}