#include "collision.h"
#include <SFML/Graphics/Image.hpp>
#include <algorithm>
#include <iostream>

bool checkPixelCollision(const Frames& frames, int frameIndex, float frameX, float frameY, const sf::FloatRect& hitbox) {
    const Frame& frame = frames.getFrame(frameIndex);
    const sf::Image& image = frames.getTextureImage();

    // Calculate the overlap region
    float overlapLeft = std::max(hitbox.left, frameX);
    float overlapTop = std::max(hitbox.top, frameY);
    float overlapRight = std::min(hitbox.left + hitbox.width, frameX + frame.w);
    float overlapBottom = std::min(hitbox.top + hitbox.height, frameY + frame.h);

    if (overlapLeft >= overlapRight || overlapTop >= overlapBottom) {
        return false;  // No overlap
    }

    // Check pixels in the overlap region
    for (int x = static_cast<int>(overlapLeft); x < static_cast<int>(overlapRight); ++x) {
        for (int y = static_cast<int>(overlapTop); y < static_cast<int>(overlapBottom); ++y) {
            // Calculate the corresponding pixel in the spritesheet
            int framePixelX = static_cast<int>(x - frameX + frame.x);
            int framePixelY = static_cast<int>(y - frameY + frame.y);

            // Check if the pixel is non-transparent
            if (image.getPixel(framePixelX, framePixelY).a > 0) {
                return true;  // Collision detected
            }
        }
    }

    return false;  // No collision
}
