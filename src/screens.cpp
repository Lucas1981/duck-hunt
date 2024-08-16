#include "screens.h"
#include <SFML/Graphics/RenderTarget.hpp>  // for RenderTarget
#include <iostream>                        // for basic_ostream, operator<<
#include "constants.h"

Screens::Screens() {
    loadScreens();
}

Screens::~Screens() {
    // Destructor
}

void Screens::loadScreens() {
    loadScreenTexture(ScreenType::TITLE_SCREEN, "../assets/title-screen.png");
    loadScreenTexture(ScreenType::FOREGROUND, "../assets/foreground-2.png");
    loadScreenTexture(ScreenType::BACKGROUND, "../assets/blue-background.png");
}

void Screens::loadScreenTexture(ScreenType screenType, const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load texture from: " << filePath << std::endl;
        return;
    }
    screenTextures[screenType] = texture;
    sf::Sprite sprite;
    sprite.setTexture(screenTextures[screenType]);
    screenSprites[screenType] = sprite;
}

void Screens::drawScreen(sf::RenderTarget& target, ScreenType screenType) {
    using namespace Constants;

    if (screenSprites.find(screenType) != screenSprites.end()) {
        screenSprites[screenType].setPosition(
            static_cast<float>(UNIT_SIZE),
            static_cast<float>(UNIT_SIZE)
        );
        target.draw(screenSprites[screenType]);
    } else {
        std::cerr << "Screen type not found!" << std::endl;
    }
}
