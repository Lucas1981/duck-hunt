#include "game.h"
#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include <SFML/Window/Keyboard.hpp>         // for Keyboard
#include <iostream>                         // for basic_ostream, operator<<
#include <iterator>                         // for next
#include "actor.h"                          // for Actor
#include "collision.h"                      // for checkHitboxCollision
#include "duck.h"                           // for Duck
#include "player.h"                         // for Player
namespace sf { class RenderTarget; }  // lines 10-10

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

    for (auto actor : actors) {
        actor->update();
    }

    for (auto it1 = actors.begin(); it1 != actors.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != actors.end(); ++it2) {
            if (
                checkHitboxCollision((*it1)->getTranslatedHitbox(),
                (*it2)->getTranslatedHitbox())
            ) {
                std::cout << "Collision detected!" << std::endl;
            }
        }
    }

    for (auto actor : actors) {
        actor->draw(renderTarget); // No offset needed
    }
    
    graphics.displayCanvas();
}

bool Game::initialize() {
    std::cout << "Initializing...\n";
    input.setWindow(graphics.getWindow());
    actors.push_back(new Duck(animator, clock));
    actors.push_back(new Player(input, animator));
    return true;
}

void Game::cleanup() {
    delete player;
    std::cout << "Goodbye!\n";
}
