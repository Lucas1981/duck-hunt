// input.cpp
#include "input.h"
#include <SFML/Graphics/RenderWindow.hpp>  // for RenderWindow
// #include <SFML/System/Vector2.inl>         // for Vector2::Vector2<T>
#include <SFML/Window/Event.hpp>           // for Event

Input::Input() {
    window = nullptr;
}

void Input::update() {
    if (!window) return;

    prevKeyState = keyState;

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            keyState[event.key.code] = true;
        } else if (event.type == sf::Event::KeyReleased) {
            keyState[event.key.code] = false;
        }
    }
}

bool Input::isKeyPressed(sf::Keyboard::Key key) {
    return keyState[key];
}

bool Input::isKeyReleased(sf::Keyboard::Key key) {
    return prevKeyState[key] && !keyState[key];
}

bool Input::isMouseButtonPressed(sf::Mouse::Button button) {
    return sf::Mouse::isButtonPressed(button);
}


sf::Vector2i Input::getMousePosition() {
    if (window) {
        return sf::Mouse::getPosition(*window);  // Get the mouse position relative to the window
    }
    return sf::Vector2i(0, 0);
}

void Input::setWindow(sf::RenderWindow& win) {
    window = &win;
}
