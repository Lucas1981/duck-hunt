#include "game.h"
#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include <SFML/Window/Keyboard.hpp>         // for Keyboard
#include <iostream>                         // for basic_ostream, char_traits
#include "player.h"                         // for Player
namespace sf { class RenderTarget; }  // lines 5-5

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

        // graphics.clearWindow();

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
    sf::RenderTarget& renderTarget = graphics.getCanvas();
    screens.drawScreen(renderTarget, ScreenType::GAME_SCREEN);
    player->update();
    player->draw(renderTarget);  // Pass the render target to draw
    graphics.displayCanvas();
}

bool Game::initialize() {
    std::cout << "Initializing...\n";
    input.setWindow(graphics.getWindow());
    player = new Player(input, animator);
    return true;
}

void Game::cleanup() {
    delete player;
    std::cout << "Goodbye!\n";
}
