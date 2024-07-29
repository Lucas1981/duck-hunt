#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include <SFML/Graphics/RenderWindow.hpp>   // for RenderWindow
namespace sf { class RenderTarget; }  // lines 6-6

class Graphics {
public:
    Graphics();
    ~Graphics();
    
    void createWindow();
    bool isWindowOpen() const;
    void clearWindow();
    void displayWindow();
    void closeWindow();
    void hideCursor();
    void showCursor();
    sf::RenderWindow& getWindow();
    sf::RenderTarget& getRenderTarget();
    void clearCanvas();
    void displayCanvas();
    sf::RenderTexture& getCanvas();

private:
    void cleanup();
    sf::RenderWindow window;
    sf::RenderTexture canvas;
};

#endif // GRAPHICS_H
