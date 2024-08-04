#include "game.h"
#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include <SFML/Window/Keyboard.hpp>         // for Keyboard
#include <iostream>                         // for basic_ostream, operator<<
#include <string>                           // for basic_string
#include "actor.h"                          // for Actor
#include "constants.h"                      // for SCREEN_WIDTH, UNIT_SIZE
#include "duck.h"                           // for Duck
#include "play.h"                           // for Play
#include "player.h"                         // for Player
#include "state.h"                          // for GameState, GameStateType

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

        if (input.isKeyPressed(sf::Keyboard::Escape) || input.isWindowClosed()) {
            graphics.closeWindow();
        }

        switch (gameState->getState()) {
            case GameStateType::TITLE_SCREEN:
                handleTitleScreenState();
                break;
            case GameStateType::RESET:
                handleResetState();
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
            case GameStateType::MISS:
                handleMissState();
                break;
            default:
                std::cerr << "Unknown game state!" << std::endl;
                return;
        }

        // Add rendering logic here
        graphics.displayCanvas();
        graphics.displayWindow();
    }
}

void Game::handleTitleScreenState() {
    if (input.isKeyPressed(sf::Keyboard::Enter)) {
        gameState->setState(GameStateType::RESET);
    }
    screens.drawScreen(graphics.getCanvas(), ScreenType::TITLE_SCREEN);
}

void Game::handleReadyState() {
    if (gameState->getTimeSinceLastStateChange() > 1) {
        actors.push_back(new Duck(animator, clock));
        gameState->setState(GameStateType::RUNNING);
    }
    play->run(false);
}

void Game::handleRunningState() {
    play->run(true);
}

void Game::handleHitState() {
    if (gameState->getTimeSinceLastStateChange() > 1) {
        gameState->setState(GameStateType::RESET);
    }
    play->run(false);
}

void Game::handleMissState() {
    play->run(false);
    text.drawText(
        graphics.getCanvas(),
        "Fly away!",
        (SCREEN_WIDTH + (2 * UNIT_SIZE)) / 2,
        300,
        TextAlignment::CENTER
    );
}

bool Game::initialize() {
    std::cout << "Initializing...\n";
    gameState = new GameState(clock);
    input.setWindow(graphics.getWindow());
    resetActors();
    play = new Play(graphics, screens, actors, gameState);

    return true;
}

void Game::handleResetState() {
    gameState->startTimeToShoot();

    if (gameState->getDucksLeft() == 0) {
        std::cout << "No ducks left\n";
        std::cout << "You shot " << gameState->getDucksShot() << " ducks!\n";
    }

    resetActors();
    gameState->reloadBullets();
    gameState->setState(GameStateType::READY);
}

void Game::resetActors() {
    actors.clear();
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
