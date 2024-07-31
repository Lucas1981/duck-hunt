#include "play.h"
#include <SFML/Graphics/RenderTexture.hpp>  // for RenderTexture
#include <iostream>                         // for char_traits, basic_ostream
#include <iterator>                         // for next
#include "actor.h"                          // for Actor
#include "collision.h"                      // for checkHitboxCollision
#include "graphics.h"                       // for Graphics
#include "screens.h"                        // for ScreenType, Screens
namespace sf { class RenderTarget; }

Play::Play(Graphics& _graphics, Screens& _screens, std::list<Actor*>& _actors)
    : graphics(_graphics), screens(_screens), actors(_actors) {}

void Play::run() {
    sf::RenderTarget& renderTarget = graphics.getCanvas();
    screens.drawScreen(renderTarget, ScreenType::GAME_SCREEN);

    for (auto actor : actors) {
        actor->update();
    }

    for (auto it1 = actors.begin(); it1 != actors.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != actors.end(); ++it2) {
            if (checkHitboxCollision((*it1)->getTranslatedHitbox(), (*it2)->getTranslatedHitbox())) {
                std::cout << "Collision detected!" << std::endl;
            }
        }
    }

    for (auto actor : actors) {
        actor->draw(renderTarget);
    }
    
    graphics.displayCanvas();
}
