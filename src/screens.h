#ifndef SCREENS_H
#define SCREENS_H

#include <SFML/Graphics/Sprite.hpp>   // for Sprite
#include <SFML/Graphics/Texture.hpp>  // for Texture
#include <string>                     // for string
#include <unordered_map>              // for unordered_map
namespace sf { class RenderTarget; }

enum class ScreenType {
    TITLE_SCREEN,
    FOREGROUND,
    BACKGROUND
};

class Screens {
public:
    Screens();
    ~Screens();
    void loadScreens();
    void drawScreen(sf::RenderTarget& target, ScreenType screenType);

private:
    std::unordered_map<ScreenType, sf::Texture> screenTextures;
    std::unordered_map<ScreenType, sf::Sprite> screenSprites;

    void loadScreenTexture(ScreenType screenType, const std::string& filePath);
};

#endif // SCREENS_H
