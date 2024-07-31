#include "game.h"
#include <SFML/Window/Keyboard.hpp>  // for Keyboard
#include <iostream>                  // for basic_ostream, char_traits, oper...
#include "actor.h"                   // for Actor
#include "duck.h"                    // for Duck
#include "play.h"                    // for Play
#include "player.h"                  // for Player

Game::Game() : play(nullptr) {}

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
    play->run();
}

bool Game::initialize() {
    std::cout << "Initializing...\n";
    input.setWindow(graphics.getWindow());
    actors.push_back(new Duck(animator, clock));
    actors.push_back(new Player(input, animator));
    play = new Play(graphics, screens, actors);
    return true;
}

void Game::cleanup() {
    delete play;
    for (auto actor : actors) {
        delete actor;
    }
    actors.clear();
    std::cout << "Goodbye!\n";
}
