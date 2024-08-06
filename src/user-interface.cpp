#include "user-interface.h"
#include "animations.h"  // for AnimationIndex
#include "animator.h"    // for Animator
#include "state.h"       // for GameState

UserInterface::UserInterface(
    GameState* _gameState, Animator& _animator
) : animator(_animator), gameState(_gameState) {}

UserInterface::~UserInterface() {

}

void UserInterface::draw(sf::RenderTarget& target) {
    for (int i = 0; i < gameState->getBullets(); i++) {
        animator.draw(
            target,
            static_cast<float>(bulletsOffsetX + (i * 32)),
            offsetY,
            Animations::AnimationIndex::BULLET,
            0
        );
    }

    for (int i = 0; i < gameState->getDucksShot(); i++) {
        animator.draw(
            target,
            static_cast<float>(ducksOffsetX + (i * 32)),
            offsetY,
            Animations::AnimationIndex::RED_DUCK,
            0
        );
    }
}