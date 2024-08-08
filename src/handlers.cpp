#include "handlers.h"
#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include <SFML/Window/Keyboard.hpp>         // for Keyboard
#include <sstream>                          // for basic_ostream, basic_stri...
#include "actor.h"                          // for Actor
#include "constants.h"                      // for SCREEN_WIDTH, UNIT_SIZE
#include "duck.h"                           // for Duck
#include "graphics.h"                       // for Graphics
#include "input.h"                          // for Input
#include "play.h"                           // for Play
#include "player.h"                         // for Player
#include "screens.h"                        // for ScreenType, Screens
#include "state.h"                          // for GameState, GameStateType
class Clock;  // lines 15-15

StateHandlers::StateHandlers(
    GameState* _gameState,
    Input& _input,
    Screens& _screens,
    Graphics& _graphics,
    Clock& _clock
) : gameState(_gameState),
    input(_input),
    screens(_screens),
    graphics(_graphics),
    clock(_clock) {
    play = new Play(graphics, screens, actors, gameState, animator, text);
}

StateHandlers::~StateHandlers() {
    delete play;
    for (auto actor : actors) {
        delete actor;
    }
    actors.clear();
}

void StateHandlers::handleTitleScreenState() {
    if (input.isKeyPressed(sf::Keyboard::Enter)) {
        gameState->resetGame();
        gameState->setState(GameStateType::ROUND_BEGIN);
    }
    screens.drawScreen(graphics.getCanvas(), ScreenType::TITLE_SCREEN);
}

void StateHandlers::handleRoundBeginState() {
    if (gameState->getTimeSinceLastStateChange() > 1) {
        gameState->setState(GameStateType::READY);
    }
    play->run(false);
    std::stringstream roundString;
    roundString << "Round " << gameState->getRound() + 1;
    drawText(roundString.str());
}

void StateHandlers::handleReadyState() {
    if (gameState->getTimeSinceLastStateChange() > 1) {
        gameState->setState(GameStateType::RESET);
    }
    play->run(false);
}

void StateHandlers::handleRunningState() {
    play->run(true);
}

void StateHandlers::handleHitState() {
    play->run(false);
}

void StateHandlers::handleMissState() {
    play->run(false);
    drawText("Fly away!");
}

// After the duck has flown away, we want to still sustain this state for another second.
void StateHandlers::handleFlownState() {
    if (gameState->getTimeSinceLastStateChange() > 1) {
        gameState->setState(GameStateType::READY);
    }
    handleMissState();
}

void StateHandlers::handleRoundWonState() {
    if (gameState->getTimeSinceLastStateChange() > 2) {
        gameState->increaseRound();
        gameState->resetDucksForRound();
        gameState->setState(GameStateType::ROUND_BEGIN);
    }
    play->run(false);
    drawText("You beat the round!");
}

void StateHandlers::handleGameOverState() {
    if (gameState->getTimeSinceLastStateChange() > 2) {
        gameState->setState(GameStateType::TITLE_SCREEN);
    }
    play->run(false);
    drawText("Game over");
}

void StateHandlers::handleFinishedState() {
    if (gameState->getTimeSinceLastStateChange() > 3) {
        gameState->setState(GameStateType::TITLE_SCREEN);
    }
    play->run(false);
    drawText("Congratulations! You beat the game!");
}

void StateHandlers::handleResetState() {
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

void StateHandlers::drawText(const std::string& str) {
    text.drawText(
        graphics.getCanvas(),
        str,
        (SCREEN_WIDTH + (2 * UNIT_SIZE)) / 2,
        VERTICAL_ANCHOR,
        TextAlignment::CENTER
    );
}

void StateHandlers::resetActors() {
    actors.clear();
    actors.push_back(new Player(input, animator));
}