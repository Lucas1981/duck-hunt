#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics/Rect.hpp>
#include "frames.h"

bool checkPixelCollision(const Frames& frames, int frameIndex, float frameX, float frameY, const sf::FloatRect& hitbox);

#endif // COLLISION_H
