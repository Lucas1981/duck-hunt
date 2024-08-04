#ifndef TEXT_MODULE_H
#define TEXT_MODULE_H

#include <SFML/Graphics/Color.hpp>  // for Color
#include <SFML/Graphics/Font.hpp>   // for Font
#include <SFML/Graphics/Text.hpp>   // for Text
#include <string>                   // for string
namespace sf { class RenderTarget; }

enum class TextAlignment {
    LEFT,
    CENTER,
    RIGHT
};

class Text {
public:
    Text();
    ~Text();

    bool loadFont(const std::string& fontPath);
    void drawText(sf::RenderTarget& target, const std::string& text, float x, float y, TextAlignment alignment);

private:
    sf::Font font;
    sf::Text sfText;
    sf::Color fillColor;
    sf::Color strokeColor;
};

#endif // TEXT_MODULE_H
