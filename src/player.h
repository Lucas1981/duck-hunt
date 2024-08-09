#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Rect.hpp>  // for FloatRect
#include "actor.h"                 // for Actor
#include "constants.h"             // for UNIT_SIZE, SCREEN_HEIGHT, SCREEN_W...
class Animator;  // lines 6-6
class Input;  // lines 7-7
class Sound;
namespace sf { class RenderTarget; }  // lines 8-8

using namespace Constants;
class Player : public Actor {
public:
    Player(Input& input, Animator& animator, Sound& _sound);
    void update() override;
    void draw(sf::RenderTarget& target) override;
    sf::FloatRect getTranslatedHitbox() const override;
    bool getShot();
    void shotHandled();

private:
    static constexpr double LEFT_BOUND = UNIT_SIZE / 2;
    static constexpr double RIGHT_BOUND = SCREEN_WIDTH + (UNIT_SIZE / 2);
    static constexpr double UPPER_BOUND = UNIT_SIZE / 2;
    static constexpr double LOWER_BOUND = SCREEN_HEIGHT + (UNIT_SIZE / 2);
    bool shot;
    bool canShoot;
    Input& input;
    Animator& animator;
    sf::FloatRect hitbox;
    Sound& sound;
};

#endif // PLAYER_H