#include "frames.h"
#include <stddef.h>                        // for size_t
#include <SFML/Graphics/Rect.hpp>          // for IntRect, Rect::Rect<T>
#include <SFML/Graphics/RenderTarget.hpp>  // for RenderTarget
#include <iostream>                        // for char_traits, basic_ostream

Frames::Frames() {
    // Default constructor
    loadTexture("../assets/spritesheet.png");
    addFrame(0, 0, 128, 128); // 0 red target
    addFrame(128, 0, 128, 128); // 1 flying right frame 1
    addFrame(256, 0, 128, 128); // 2 flying right frame 2
    addFrame(384, 0, 128, 128); // 3 shot
    addFrame(0, 128, 128, 128); // 4 Falling, LTR
    addFrame(128, 128, 128, 128); // 5 Falling, RTL
    addFrame(256, 128, 32, 32); // 6 Bullet
    addFrame(256, 160, 32, 32); // 7 White ducky
    addFrame(256, 192, 32, 32); // 8 Red ducky
    addFrame(256, 224, 32, 32); // 9 Black ducky
    addFrame(288, 128, 32, 32); // 10 Target
    addFrame(288, 160, 32, 32); // 11 Score
}

void Frames::loadTexture(const std::string& filePath) {
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load texture from: " << filePath << std::endl;
    } else {
        sprite.setTexture(texture);
    }
}

void Frames::addFrame(float x, float y, float w, float h) {
    frames.push_back({x, y, w, h});
}

void Frames::draw(sf::RenderTarget& target, float dx, float dy, int frameIndex) {
    if (frameIndex < 0 || frameIndex >= static_cast<int>(frames.size())) {
        std::cerr << "Invalid frame index: " << frameIndex << std::endl;
        return;
    }
    const Frame& frame = frames[static_cast<size_t>(frameIndex)];
    sprite.setTextureRect(sf::IntRect(
        static_cast<int>(frame.x),
        static_cast<int>(frame.y),
        static_cast<int>(frame.w),
        static_cast<int>(frame.h))
    );
    sprite.setPosition(dx, dy);
    target.draw(sprite);
}
