#include "graphics.h"
#include <SFML/System/String.hpp>     // for String
#include <SFML/Window/VideoMode.hpp>  // for VideoMode
#include "constants.h"

namespace sf { class RenderTarget; }
using namespace Constants;

Graphics::Graphics() {
    createWindow();
}

Graphics::~Graphics() {
    cleanup();
}

void Graphics::createWindow() {
    window.create(sf::VideoMode((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT), "Duck Hunt");
    hideCursor();
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

void Graphics::cleanup() {
    showCursor();  // Show the cursor when the window is closed
    if (window.isOpen()) {
        window.close();
    }
}