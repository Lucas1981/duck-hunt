#include "text.h"
#include <SFML/Graphics/Rect.hpp>          // for FloatRect
#include <SFML/Graphics/RenderTarget.hpp>  // for RenderTarget
#include <SFML/System/String.hpp>          // for String
#include <iostream>                        // for basic_ostream, operator<<

Text::Text()
    : fillColor(sf::Color::White), strokeColor(sf::Color(128, 128, 128)) {
    sfText.setFillColor(fillColor);
    sfText.setOutlineColor(strokeColor);
    sfText.setOutlineThickness(2.0f);
    loadFont("../assets/font.ttf");
}

Text::~Text() {
    // Destructor
}

bool Text::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from: " << fontPath << std::endl;
        return false;
    }
    sfText.setFont(font); // Update the font of sfText
    return true;
}

void Text::drawText(sf::RenderTarget& target, const std::string& text, float x, float y, TextAlignment alignment) {
    sfText.setString(text);

    // Calculate the position based on alignment
    sf::FloatRect textBounds = sfText.getLocalBounds();
    switch (alignment) {
        case TextAlignment::LEFT:
            sfText.setPosition(x, y);
            break;
        case TextAlignment::CENTER:
            sfText.setPosition(x - textBounds.width / 2.0f, y);
            break;
        case TextAlignment::RIGHT:
            sfText.setPosition(x - textBounds.width, y);
            break;
    }

    target.draw(sfText);
}
