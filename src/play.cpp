#include "play.h"
#include <SFML/Graphics/Rect.hpp>           // for FloatRect
#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include "actor.h"                          // for Actor
#include "collision.h"                      // for checkHitboxCollision
#include "duck.h"                           // for Duck
#include "graphics.h"                       // for Graphics
#include "player.h"                         // for Player
#include "score.h"                          // for Score
#include "screens.h"                        // for ScreenType, Screens
#include "state.h"                          // for GameState, GameStateType
#include "user-interface.h"                 // for UserInterface
class Animator;  // lines 14-14
namespace sf { class RenderTarget; }  // lines 15-15

Play::Play(
    Graphics& _graphics,
    Screens& _screens,
    std::list<Actor*>& _actors,
    GameState* _gameState,
    Animator& _animator,
    Text& text,
    Clock& _clock
) : animator(_animator),
    graphics(_graphics),
    screens(_screens),
    gameState(_gameState),
    actors(_actors),
    clock(_clock)
{
    userInterface = new UserInterface(gameState, animator, text);
}

Play::~Play() {
    delete userInterface;
}

void Play::run(bool handleInput) {
    update();
    removeInactiveActors();
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

        if (!actor->isOpponent()) {
            continue;
        }

        // At this point we can safely typecast to a duck
        Duck* duck = static_cast<Duck*>(actor);

        if (
            duck->isUpperThresholdReached()
        ) {
            duck->deactivate();
            gameState->decreaseDucks();
            gameState->setState(GameStateType::FLOWN);
        }

        if (
            duck->isFalling() &&
            duck->isLowerThresholdReached()
        ) {
            duck->deactivate();
            gameState->setState(GameStateType::READY);
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

    if (!player->getShot()) {
        return;
    }

    gameState->decreaseBullets();
    sf::FloatRect playerHitbox = player->getTranslatedHitbox();
    for (auto it1 = actors.begin(); it1 != actors.end(); ++it1) {
        if (!(*it1)->isOpponent()) {
            continue;
        }

        Duck* duck = static_cast<Duck*>(*it1);

        if (checkHitboxCollision(duck->getTranslatedHitbox(), playerHitbox)) {
            duck->handleShot();
            gameState->decreaseDucks();
            gameState->increaseDucksShot();
            gameState->markAuditDuckAsShot(gameState->getDuckAuditIndex() - 1);
            actors.push_back(new Score(animator, clock, duck->getX(), duck->getY()));
            gameState->setState(GameStateType::HIT);
            break;
        } else if (gameState->getBullets() == 0) {
            duck->handleEscaping();
            gameState->setState(GameStateType::MISS);
        }
    }

    player->shotHandled();
}

void Play::removeInactiveActors() {
    for (auto it = actors.begin(); it != actors.end(); ) {
        if (!(*it)->isActive()) {
            delete *it;
            it = actors.erase(it);
        } else {
            ++it;
        }
    }
}

void Play::draw() {
    sf::RenderTarget& renderTarget = graphics.getCanvas();
    screens.drawScreen(renderTarget, ScreenType::GAME_SCREEN);

    for (Actor* actor : actors) {
        actor->draw(renderTarget);
    }

    userInterface->draw(graphics.getCanvas());
}