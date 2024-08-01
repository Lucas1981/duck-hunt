#include "game.h"
#include <SFML/Window/Keyboard.hpp>  // for Keyboard
#include <iostream>                  // for basic_ostream, char_traits, oper...
#include "actor.h"                   // for Actor
#include "duck.h"                    // for Duck
#include "play.h"                    // for Play
#include "player.h"                  // for Player
#include "state.h"                   // for GameState, GameStateType

Game::Game() : gameState(nullptr), play(nullptr) {}

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

        switch (gameState->getState()) {
            case GameStateType::TITLE_SCREEN:
                // handleTitleScreenState();
                break;
            case GameStateType::READY:
                handleReadyState();
                break;
            case GameStateType::RUNNING:
                handleRunningState();
                break;
            case GameStateType::HIT:
                handleHitState();
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
    play->run(true);
}

void Game::handleHitState() {
    if (gameState->getTimeSinceLastStateChange() > 1) {
        reset();
        gameState->setState(GameStateType::RUNNING);
    }
    play->run(false);
}

bool Game::initialize() {
    std::cout << "Initializing...\n";
    gameState = new GameState(clock);
    input.setWindow(graphics.getWindow());
    reset();
    play = new Play(graphics, screens, actors, gameState);
    return true;
}

void Game::reset() {
    actors.clear();
    actors.push_back(new Duck(animator, clock));
    actors.push_back(new Player(input, animator));
}

void Game::cleanup() {
    delete play;
    for (auto actor : actors) {
        delete actor;
    }
    actors.clear();
    delete gameState;
    std::cout << "Goodbye!\n";
}
