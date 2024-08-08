#include "game.h"
#include <SFML/Window/Keyboard.hpp>  // for Keyboard
#include <iostream>                  // for basic_ostream, char_traits, oper...
#include "handlers.h"                // for StateHandlers
#include "state.h"                   // for GameStateType, GameState

Game::Game() : gameState(nullptr) {}

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

        if (input.isKeyPressed(sf::Keyboard::Escape) || input.isWindowClosed()) {
            graphics.closeWindow();
        }

        switch (gameState->getState()) {
            case GameStateType::TITLE_SCREEN:
                stateHandlers->handleTitleScreenState();
                break;
            case GameStateType::ROUND_BEGIN:
                stateHandlers->handleRoundBeginState();
                break;
            case GameStateType::RESET:
                stateHandlers->handleResetState();
                break;
            case GameStateType::READY:
                stateHandlers->handleReadyState();
                break;
            case GameStateType::RUNNING:
                stateHandlers->handleRunningState();
                break;
            case GameStateType::HIT:
                stateHandlers->handleHitState();
                break;
            case GameStateType::MISS:
                stateHandlers->handleMissState();
                break;
            case GameStateType::FLOWN:
                stateHandlers->handleFlownState();
                break;
            case GameStateType::TALLY:
                stateHandlers->handleTallyState();
                break;
            case GameStateType::HOLD:
                stateHandlers->handleHoldState();
                break;
            case GameStateType::ROUND_WON:
                stateHandlers->handleRoundWonState();
                break;
            case GameStateType::GAME_OVER:
                stateHandlers->handleGameOverState();
                break;
            case GameStateType::FINISHED:
                stateHandlers->handleFinishedState();
                break;
            default:
                std::cerr << "Unknown game state!" << std::endl;
                return;
        }

        graphics.displayCanvas();
        graphics.displayWindow();
    }
}

bool Game::initialize() {
    std::cout << "Initializing...\n";
    gameState = new GameState(clock);
    input.setWindow(graphics.getWindow());
    stateHandlers = new StateHandlers(gameState, input, screens, graphics, clock);
    return true;
}

void Game::cleanup() {
    delete stateHandlers;
    delete gameState;
    std::cout << "Goodbye!\n";
}
