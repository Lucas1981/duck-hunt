#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>  // for hitbox
#include "clock.h"
// #include "animator.h"
class Animator;

enum class AgentType {
    PLAYER,
    DUCK,
};

enum class AgentState {
    IDLE,
    FLYING,
    SHOT,
    FALLING,
    DEAD
};

class Actor {
public:
    virtual ~Actor() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target) = 0;

protected:
    double x;
    double y;
    AgentType type;
    AgentState state;
    sf::FloatRect hitbox;
    Animator* animator;
};

#endif // ACTOR_H