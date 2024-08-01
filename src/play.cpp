#include "play.h"
#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include <SFML/Graphics/Rect.hpp>  // for hitbox
#include <iostream>                         // for basic_ostream, char_traits
#include "actor.h"                          // for Actor
#include "collision.h"                      // for checkHitboxCollision
#include "graphics.h"                       // for Graphics
#include "player.h"                         // for Player
#include "screens.h"                        // for ScreenType, Screens
namespace sf { class RenderTarget; }  // lines 10-10

Play::Play(Graphics& _graphics, Screens& _screens, std::list<Actor*>& _actors)
    : graphics(_graphics), screens(_screens), actors(_actors) {}

void Play::run() {
    sf::RenderTarget& renderTarget = graphics.getCanvas();
    screens.drawScreen(renderTarget, ScreenType::GAME_SCREEN);

    for (auto actor : actors) {
        actor->update();
    }

    // Find the player agent
    Player* player = nullptr;
    for (auto actor : actors) {
        if (actor->isPlayer()) {
            player = static_cast<Player*>(actor);
            break;
        }
    }

    if (player->getShot()) {
        std::cout << "Shot fired!" << std::endl;
        sf::FloatRect playerHitbox = player->getTranslatedHitbox();
        for (auto it1 = actors.begin(); it1 != actors.end(); ++it1) {
            if ((*it1)->isPlayer()) {
                continue;
            }

            if (checkHitboxCollision((*it1)->getTranslatedHitbox(), playerHitbox)) {
                std::cout << "Target shot!" << std::endl;
            }
        }
        player->shotHandled();
    }

    for (auto actor : actors) {
        actor->draw(renderTarget);
    }
    
    graphics.displayCanvas();
}