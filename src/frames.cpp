#include "frames.h"
#include <stddef.h>                        // for size_t
#include <SFML/Graphics/Rect.hpp>          // for IntRect, Rect::Rect<T>
#include <SFML/Graphics/RenderTarget.hpp>  // for RenderTarget
#include <iostream>                        // for char_traits, basic_ostream

Frames& Frames::getInstance() {
    static Frames instance;
    return instance;
}

Frames::Frames() {
    // Default constructor
    loadTexture("../assets/spritesheet.png");
    addFrame(0, 0, 128, 128);
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
    if (frameIndex < 0 || frameIndex >= (int)frames.size()) {
        std::cerr << "Invalid frame index: " << frameIndex << std::endl;
        return;
    }
    const Frame& frame = frames[(size_t)frameIndex];
    sprite.setTextureRect(sf::IntRect(static_cast<int>(frame.x), static_cast<int>(frame.y), static_cast<int>(frame.w), static_cast<int>(frame.h)));
    sprite.setPosition(dx, dy);
    target.draw(sprite);
}
