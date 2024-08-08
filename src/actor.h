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
    ESCAPING,
    SHOT,
    FALLING,
};

class Actor {
public:
    virtual ~Actor() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual sf::FloatRect getTranslatedHitbox() const = 0;
    bool isPlayer() const { return type == AgentType::PLAYER; }
    bool isActive() { return active; }
    void deactivate() { active = false; }
    double getY() { return y; }

protected:
    Actor() : active(true) {} 

    double x;
    double y;
    bool active;
    AgentType type;
    AgentState state;
    Animator* animator;
};

#endif // ACTOR_H
