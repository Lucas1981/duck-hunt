#include "game.h"
#include <SFML/Window/Keyboard.hpp>  // for Keyboard
#include <iostream>                  // for basic_ostream, char_traits, oper...
#include "player.h"                  // for Player

Game::Game() : player(nullptr) {}

Game::~Game() {
    cleanup();
}

void Game::run() {
    if (!initialize()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return;
    }

    while (graphics.isWindowOpen()) {
        clock.setTimer();
        input.update();

        if (input.isKeyPressed(sf::Keyboard::Escape)) {
            graphics.closeWindow();
        }

        graphics.clearWindow();

        switch (gameState.getState()) {
            case GameStateType::TITLE_SCREEN:
                // handleTitleScreenState();
                break;
            case GameStateType::READY:
                handleReadyState();
                break;
            case GameStateType::RUNNING:
                handleRunningState();
                break;
            default:
                std::cerr << "Unknown game state!" << std::endl;
                return;
        }

        // Add rendering logic here
        graphics.displayWindow();
    }
}

void Game::handleReadyState() {
    // Implementation for the READY state
}

void Game::handleRunningState() {
    player->update();
    player->draw(graphics.getRenderTarget());  // Pass the render target to draw
}

bool Game::initialize() {
    std::cout << "Initializing...\n";
    input.setWindow(graphics.getWindow());
    player = new Player(input, clock);
    return true;
}

void Game::cleanup() {
    delete player;
    std::cout << "Goodbye!\n";
}
