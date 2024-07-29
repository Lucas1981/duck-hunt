#include "player.h"
#include <SFML/Graphics/Rect.hpp>   // for FloatRect, Rect::Rect<T>
#include <SFML/System/Vector2.hpp>  // for Vector2i
#include "animations.h"             // for AnimationIndex
#include "clock.h"                  // for Clock
#include "input.h"                  // for Input
namespace sf { class RenderTarget; }  // lines 8-8

Player::Player(Input& _input, Clock& _clock)
    : input(_input), clock(_clock), animator(Animations::CROSSHAIRS) {
    x = 240.0;
    y = 240.0;
    type = AgentType::PLAYER;
    state = AgentState::IDLE;
    hitbox = sf::FloatRect((float)x, (float)y, 32, 32);  // Example hitbox size
    // animator = new Animator();
}

void Player::draw(sf::RenderTarget& target) {
    // animator->draw(target, static_cast<float>(x), static_cast<float>(y));
    // std::cout << x << ' ' << y << '\n';
    animator.draw(target, static_cast<float>(x), static_cast<float>(y));
}

void Player::update() {
    double elapsedTime = clock.getElapsedTime();
    animator.update((float)elapsedTime);
    sf::Vector2i mousePosition = input.getMousePosition();
    x = static_cast<double>(mousePosition.x);
    y = static_cast<double>(mousePosition.y);

    if (x < LEFT_BOUND) x = LEFT_BOUND;
    if (x > RIGHT_BOUND) x = RIGHT_BOUND;
    if (y < UPPER_BOUND) y = UPPER_BOUND;
    if (y > LOWER_BOUND) y = LOWER_BOUND;
}