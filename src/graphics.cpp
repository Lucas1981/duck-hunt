#include "graphics.h"
#include <stddef.h>                   // for size_t
#include <SFML/Graphics/Rect.hpp>     // for IntRect, Rect::Rect<T>
#include <SFML/Graphics/Sprite.hpp>   // for Sprite
#include <SFML/System/String.hpp>     // for String
#include <SFML/Window/VideoMode.hpp>  // for VideoMode
#include "constants.h"                // for SCREEN_HEIGHT, UNIT_SIZE, SCREE...
namespace sf { class RenderTarget; }  // lines 9-9

using namespace Constants;

Graphics::Graphics() {
    createWindow();
    hideCursor();
    canvas.create((int)SCREEN_WIDTH + (size_t)(2 * UNIT_SIZE), (int)SCREEN_HEIGHT + (size_t)(UNIT_SIZE * 2));
}

Graphics::~Graphics() {
    cleanup();
}

void Graphics::createWindow() {
    window.create(sf::VideoMode((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT), "Duck Hunt");
}

bool Graphics::isWindowOpen() const {
    return window.isOpen();
}

void Graphics::clearWindow() {
    window.clear();
}

void Graphics::displayWindow() {
    window.display();
}

void Graphics::closeWindow() {
    window.close();
}

sf::RenderWindow& Graphics::getWindow() {
    return window;
}

sf::RenderTarget& Graphics::getRenderTarget() {
    return window;
}

void Graphics::hideCursor() {
    window.setMouseCursorVisible(false);
}

void Graphics::showCursor() {
    window.setMouseCursorVisible(true);
}

void Graphics::clearCanvas() {
    canvas.clear();
}

void Graphics::displayCanvas() {
    sf::Sprite sprite(canvas.getTexture());

    sprite.setTextureRect(sf::IntRect(
        (int)UNIT_SIZE,
        (int)SCREEN_HEIGHT + (int)UNIT_SIZE,
        (int)(SCREEN_WIDTH),
        -1 * (int)(SCREEN_HEIGHT)
    ));

    window.draw(sprite);
}

sf::RenderTexture& Graphics::getCanvas() {
    return canvas;
}
    
void Graphics::cleanup() {
    showCursor();  // Show the cursor when the window is closed
    if (window.isOpen()) {
        window.close();
    }
}