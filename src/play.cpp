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
#include "sound.h"
class Animator;
class Clock;
class Text;
namespace sf { class RenderTarget; }

Play::Play(
    Graphics& _graphics,
    Screens& _screens,
    std::list<Actor*>& _actors,
    GameState* _gameState,
    Animator& _animator,
    Text& text,
    Clock& _clock,
    Sound& _sound,
    Input& input
) : graphics(_graphics),
    screens(_screens),
    actors(_actors),
    gameState(_gameState),
    clock(_clock),
    animator(_animator),
    sound(_sound) {
    userInterface = new UserInterface(gameState, animator, text);
    player = new Player(input, gameState, animator, sound);
}

Play::~Play() {
    delete player;
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

    if (gameState->getState() == GameStateType::RUNNING && gameState->timeToShootExpired()) {
        gameState->setState(GameStateType::MISS);
        isStateChanged = true;
    }

    player->update();
    for (Actor* actor : actors) {
        handleActorUpdate(actor, isStateChanged);
    }
}

void Play::handleActorUpdate(Actor* actor, bool& isStateChanged) {
    actor->update();

    if (!actor->isOpponent()) return;

    Duck* duck = static_cast<Duck*>(actor);

    if (duck->isUpperThresholdReached()) {
        duck->deactivate();
        gameState->decreaseDucks();
        gameState->setState(GameStateType::FLOWN);
    } else if (duck->isFalling() && duck->isLowerThresholdReached()) {
        sound.stopAll();
        sound.enqueue(SoundEffect::DROP);
        duck->deactivate();
        gameState->setState(GameStateType::READY);
    } else if (isStateChanged) {
        duck->handleEscaping();
    }
}

void Play::inputHandler() {
    if (!player->getShot()) return;

    gameState->decreaseBullets();
    handlePlayerShot();
    player->shotHandled();
    sound.enqueue(SoundEffect::SHOOT);
}

void Play::handlePlayerShot() {
    sf::FloatRect playerHitbox = player->getTranslatedHitbox();

    for (Actor* actor : actors) {
        if (!actor->isOpponent()) continue;

        Duck* duck = static_cast<Duck*>(actor);

        if (checkHitboxCollision(duck->getTranslatedHitbox(), playerHitbox)) {
            sound.stopAll();
            handleDuckShot(duck);
            return;
        } else if (gameState->getBullets() == 0) {
            duck->handleEscaping();
            gameState->setState(GameStateType::MISS);
            return;
        }
    }
}

void Play::handleDuckShot(Duck* duck) {
    duck->handleShot();
    gameState->decreaseDucks();
    gameState->increaseDucksShot();
    gameState->markAuditDuckAsShot(gameState->getDuckAuditIndex() - 1);
    actors.push_front(new Score(animator, clock, duck->getX(), duck->getY()));
    gameState->setState(GameStateType::HIT);
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
    screens.drawScreen(renderTarget, ScreenType::BACKGROUND);

    for (Actor* actor : actors) {
        actor->draw(renderTarget);
    }

    screens.drawScreen(renderTarget, ScreenType::FOREGROUND);

    userInterface->draw(graphics.getCanvas());

    player->draw(renderTarget);
}
