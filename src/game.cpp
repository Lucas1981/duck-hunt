#include "game.h"
#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include <SFML/Window/Keyboard.hpp>         // for Keyboard
#include <iostream>                         // for basic_ostream, operator<<
#include <sstream>                          // for basic_stringstream, strin...
#include <string>                           // for char_traits, allocator
#include "actor.h"                          // for Actor
#include "constants.h"                      // for UNIT_SIZE, SCREEN_WIDTH
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
            case GameStateType::ROUND_BEGIN:
                handleRoundBeginState();
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
            case GameStateType::FLOWN:
                handleFlownState();
                break;
            case GameStateType::ROUND_WON:
                handleRoundWonState();
                break;
            case GameStateType::GAME_OVER:
                handleGameOverState();
                break;
            case GameStateType::FINISHED:
                handleFinishedState();
                break;
            default:
                std::cerr << "Unknown game state!" << std::endl;
                return;
        }

        graphics.displayCanvas();
        graphics.displayWindow();
    }
}

void Game::handleTitleScreenState() {
    if (input.isKeyPressed(sf::Keyboard::Enter)) {
        gameState->resetGame();
        gameState->setState(GameStateType::ROUND_BEGIN);
    }
    screens.drawScreen(graphics.getCanvas(), ScreenType::TITLE_SCREEN);
}

void Game::handleRoundBeginState() {
    if (gameState->getTimeSinceLastStateChange() > 1) {
        gameState->setState(GameStateType::READY);
    }
    play->run(false);
    std::stringstream roundString;
    roundString << "Round " << gameState->getRound() + 1;
    drawText(roundString.str());
}

void Game::handleReadyState() {
    if (gameState->getTimeSinceLastStateChange() > 1) {
        gameState->setState(GameStateType::RESET);
    }
    play->run(false);
}

void Game::handleRunningState() {
    play->run(true);
}

void Game::handleHitState() {
    play->run(false);
}

void Game::handleMissState() {
    play->run(false);
    drawText("Fly away!");
}

// After the duck has flown away, we want to still sustain this state for another second.
void Game::handleFlownState() {
    if (gameState->getTimeSinceLastStateChange() > 1) {
        gameState->setState(GameStateType::READY);
    }
    handleMissState();
}

void Game::handleRoundWonState() {
    if (gameState->getTimeSinceLastStateChange() > 2) {
        gameState->increaseRound();
        gameState->resetDucksForRound();
        gameState->setState(GameStateType::ROUND_BEGIN);
    }
    play->run(false);
    drawText("You beat the round!");
}

void Game::handleGameOverState() {
    if (gameState->getTimeSinceLastStateChange() > 2) {
        gameState->setState(GameStateType::TITLE_SCREEN);
    }
    play->run(false);
    drawText("Game over");
}

void Game::handleFinishedState() {
    if (gameState->getTimeSinceLastStateChange() > 3) {
        gameState->setState(GameStateType::TITLE_SCREEN);
    }
    play->run(false);
    drawText("Congratulations! You beat the game!");
}

void Game::handleResetState() {
    if (gameState->isRoundEnd()) {
        if (gameState->isTargetMet()) {
            if (gameState->isGameFinished()) {
                gameState->setState(GameStateType::FINISHED);
            } else {
                gameState->setState(GameStateType::ROUND_WON);
            }
        } else {
            gameState->setState(GameStateType::GAME_OVER);
        }
    } else {
        resetActors();
        gameState->startTimeToShoot();
        actors.push_front(new Duck(animator, clock, gameState->getRoundSpeed()));
        gameState->reloadBullets();
        gameState->setState(GameStateType::RUNNING);
    }
}

void Game::drawText(const std::string& str) {
    text.drawText(
        graphics.getCanvas(),
        str,
        (SCREEN_WIDTH + (2 * UNIT_SIZE)) / 2,
        VERTICAL_ANCHOR,
        TextAlignment::CENTER
    );
}

void Game::resetActors() {
    actors.clear();
    actors.push_back(new Player(input, animator));
}

bool Game::initialize() {
    std::cout << "Initializing...\n";
    gameState = new GameState(clock);
    input.setWindow(graphics.getWindow());
    resetActors();
    play = new Play(graphics, screens, actors, gameState, animator, text);
    return true;
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
