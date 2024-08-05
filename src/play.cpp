#include "play.h"
#include <SFML/Graphics/Rect.hpp>           // for FloatRect
#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include "actor.h"                          // for Actor
#include "collision.h"                      // for checkHitboxCollision
#include "duck.h"                           // for Duck
#include "graphics.h"                       // for Graphics
#include "player.h"                         // for Player
#include "screens.h"                        // for ScreenType, Screens
#include "state.h"                          // for GameState, GameStateType
namespace sf { class RenderTarget; }  // lines 11-11

Play::Play(Graphics& _graphics, Screens& _screens, std::list<Actor*>& _actors, GameState* _gameState)
    : graphics(_graphics), screens(_screens), gameState(_gameState), actors(_actors) {}

void Play::run(bool handleInput) {
    update();
    if (handleInput) {
        inputHandler();
    }
    draw();
}

void Play::update() {
    bool isStateChanged = false;
    if (
        gameState->getState() == GameStateType::RUNNING &&
        gameState->timeToShootExpired()
    ) {
        gameState->setState(GameStateType::MISS);
        isStateChanged = true;
    }

    for (auto actor : actors) {
        actor->update();

        if (actor->isPlayer()) {
            continue;
        }

        // At this point we can safely typecast to a duck
        Duck* duck = static_cast<Duck*>(actor);

        if (
            !duck->isEscaped() &&
            duck->isUpperThresholdReached()
        ) {
            duck->handleEscaped();
            gameState->decreaseDucks();
            gameState->setState(GameStateType::FLOWN);
        }

        if (
            duck->isFalling() &&
            duck->isLowerThresholdReached()
        ) {
            gameState->setState(GameStateType::RESET);
        }

        if (isStateChanged) {
            duck->handleEscaping();
        }
    }
}

void Play::inputHandler() {
    Player* player = nullptr;
    for (auto actor : actors) {
        if (actor->isPlayer()) {
            player = static_cast<Player*>(actor);
            break;
        }
    }

    if (player->getShot()) {
        gameState->decreaseBullets();
        sf::FloatRect playerHitbox = player->getTranslatedHitbox();

        for (auto it1 = actors.begin(); it1 != actors.end(); ++it1) {
            if ((*it1)->isPlayer()) {
                continue;
            }

            Duck* duck = static_cast<Duck*>(*it1);

            if (checkHitboxCollision(duck->getTranslatedHitbox(), playerHitbox)) {
                duck->handleShot();
                gameState->decreaseDucks();
                gameState->increaseDucksShot();
                gameState->setState(GameStateType::HIT);
            } else if (gameState->getBullets() == 0) {
                duck->handleEscaping();
                gameState->setState(GameStateType::MISS);
            }
        }

        player->shotHandled();
    }
}

void Play::draw() {
    sf::RenderTarget& renderTarget = graphics.getCanvas();
    screens.drawScreen(renderTarget, ScreenType::GAME_SCREEN);

    for (Actor* actor : actors) {
        actor->draw(renderTarget);
    }
}