#ifndef INPUT_H
#define INPUT_H

#include <SFML/System/Vector2.hpp>   // for Vector2i
#include <SFML/Window/Keyboard.hpp>  // for Keyboard
#include <SFML/Window/Mouse.hpp>     // for Mouse
#include <unordered_map>             // for unordered_map
namespace sf { class RenderWindow; }  // lines 7-7

class Input {
public:
    Input();
    void update();
    bool isKeyPressed(sf::Keyboard::Key key);
    bool isKeyReleased(sf::Keyboard::Key key);
    bool isMouseButtonPressed(sf::Mouse::Button button);
    sf::Vector2i getMousePosition();  // Add this method

    void setWindow(sf::RenderWindow& win);

private:
    sf::RenderWindow* window;
    std::unordered_map<sf::Keyboard::Key, bool> keyState;
    std::unordered_map<sf::Keyboard::Key, bool> prevKeyState;
};

#endif // INPUT_H
