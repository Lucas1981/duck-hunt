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
#include "screens.h"                        // for ScreenType, Screens
#include "state.h"                          // for GameState, GameStateType
#include "sound.h"
class Clock;  // lines 15-15

StateHandlers::StateHandlers(
    GameState* _gameState,
    Input& _input,
    Screens& _screens,
    Graphics& _graphics,
    Clock& _clock,
    Sound& _sound
) : gameState(_gameState),
    input(_input),
    screens(_screens),
    graphics(_graphics),
    clock(_clock),
    sound(_sound) {
    play = new Play(
        graphics,
        screens,
        actors,
        gameState,
        animator,
        text,
        clock,
        sound,
        input
    );
    resetActors();
}

StateHandlers::~StateHandlers() {
    delete play;
    resetActors();
}

void StateHandlers::handleTitleScreenState() {
    if (input.isKeyPressed(sf::Keyboard::Enter)) {
        gameState->resetGame();
        sound.stopAll();
        setupRoundBegin();
    }
    screens.drawScreen(graphics.getCanvas(), ScreenType::TITLE_SCREEN);
    text.drawText(
        graphics.getCanvas(),
        "Press enter to start",
        (SCREEN_WIDTH + (2 * UNIT_SIZE)) / 2,
        730,
        TextAlignment::CENTER
    );
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

void StateHandlers::handleTallyState() {
    bool result = gameState->performTally();

    if (result) {
        sound.enqueue(SoundEffect::TALLY);
        gameState->setState(GameStateType::HOLD);
    } else {
        if (gameState->isTargetMet()) {
            if (gameState->isGameFinished()) {
                sound.enqueue(SoundEffect::GAME_WON);
                gameState->setState(GameStateType::FINISHED);
            } else {
                sound.enqueue(SoundEffect::ROUND_BEAT);
                gameState->setState(GameStateType::ROUND_WON);
            }
        } else {
            sound.enqueue(SoundEffect::GAME_OVER);
            gameState->setState(GameStateType::GAME_OVER);
        }
    }
    play->run(false);
}

void StateHandlers::handleHoldState() {
    if (gameState->getTimeSinceLastStateChange() > 0.4) {
        gameState->setState(GameStateType::TALLY);
    }
    play->run(false);
}

void StateHandlers::handleRoundWonState() {
    if (gameState->getTimeSinceLastStateChange() > 3) {
        gameState->increaseRound();
        gameState->resetDucksForRound();
        setupRoundBegin();
    }
    play->run(false);
    drawText("You beat the round!");
}

void StateHandlers::handleGameOverState() {
    if (gameState->getTimeSinceLastStateChange() > 3) {
        setupTitleScreen();
    }
    play->run(false);
    drawText("Game over");
}

void StateHandlers::handleFinishedState() {
    if (gameState->getTimeSinceLastStateChange() > 3) {
        setupTitleScreen();
    }
    play->run(false);
    drawText("Congratulations! You beat the game!");
}

void StateHandlers::handleResetState() {
    if (gameState->isRoundEnd()) {
        gameState->setState(GameStateType::TALLY);
    } else {
        resetActors();
        gameState->startTimeToShoot();
        actors.push_front(new Duck(animator, clock, sound, gameState->getRoundSpeed()));
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
    for (auto actor : actors) {
        delete actor;
    }
    actors.clear();
}

void StateHandlers::setupRoundBegin() {
    gameState->setState(GameStateType::ROUND_BEGIN);
    sound.enqueue(SoundEffect::NEW_LEVEL);
}

void StateHandlers::setupTitleScreen() {
    sound.enqueue(SoundEffect::TITLE_SCREEN);
    gameState->setState(GameStateType::TITLE_SCREEN);
}
