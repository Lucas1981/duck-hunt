#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics/RenderWindow.hpp>  // for RenderWindow
namespace sf { class RenderTarget; }

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

private:
    void cleanup();
    sf::RenderWindow window;
};

#endif // GRAPHICS_H
