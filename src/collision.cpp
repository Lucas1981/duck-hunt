#include "collision.h"

bool checkHitboxCollision(const sf::FloatRect& hitbox1, const sf::FloatRect& hitbox2) {
    return hitbox1.intersects(hitbox2);
}
