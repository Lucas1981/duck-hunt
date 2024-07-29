#ifndef FRAMES_H
#define FRAMES_H

#include <SFML/Graphics/Sprite.hpp>   // for Sprite
#include <SFML/Graphics/Texture.hpp>  // for Texture
#include <string>                     // for string
#include <vector>                     // for vector
namespace sf { class RenderTarget; }

struct Frame {
    float x;
    float y;
    float w;
    float h;
};

class Frames {
public:
    Frames();
    ~Frames() = default;

    void loadTexture(const std::string& filePath);
    void addFrame(float x, float y, float w, float h);
    void draw(sf::RenderTarget& target, float dx, float dy, int frameIndex);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<Frame> frames;
};

#endif // FRAMES_H
