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
    hitbox = sf::FloatRect(0, 0, UNIT_SIZE, UNIT_SIZE);  // Example hitbox size
    startTime = clock.getCurrentTime();
}

Duck::~Duck() {
    // Handle destruction
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
        Animations::FLY_HORIZONTAL_RIGHT,
        static_cast<float>(elapsedTime)
    );
}
