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
    
    graphics.displayCanvas();
}

void Play::update() {
    for (auto actor : actors) {
        actor->update();
        if (!actor->isPlayer() && actor->getY() == 0) {
            gameState->setState(GameStateType::RESET);
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

            if (checkHitboxCollision((*it1)->getTranslatedHitbox(), playerHitbox)) {
                (static_cast<Duck*>(*it1))->handleShot();
                gameState->setState(GameStateType::HIT);
            } else if (gameState->getBullets() == 0) {
                (static_cast<Duck*>(*it1))->handleEscaped();
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