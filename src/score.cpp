#include "score.h"
#include <chrono>        // for duration, operator-, time_point
#include "animations.h"  // for AnimationIndex
#include "animator.h"    // for Animator
#include <SFML/Graphics/Rect.hpp>  // for FloatRect, Rect::Rect<T>
#include "constants.h"
namespace sf { class RenderTarget; }

using namespace Constants;

Score::Score(Animator& _animator, Clock& _clock, double initialX, double initialY)
    : animator(_animator), clock(_clock), spawnTime(_clock.getCurrentTime()) {
    x = initialX;
    y = initialY;
    type = AgentType::SCORE;
    state = AgentState::IDLE;
}

Score::~Score() {
    // Handle destruction if needed
}

void Score::update() {
    auto currentTime = clock.getCurrentTime();
    double elapsedTime = std::chrono::duration<double>(currentTime - spawnTime).count();
    
    y -= SPEED * elapsedTime;

    if (y < 0 || elapsedTime > LIFESPAN) {
        deactivate();
    }
}

void Score::draw(sf::RenderTarget& target) {
    animator.draw(
        target,
        static_cast<float>(x),
        static_cast<float>(y),
        Animations::AnimationIndex::SCORE,
        0
    );
}

sf::FloatRect Score::getTranslatedHitbox() const {
    return sf::FloatRect(0, 0, 0, 0);
}