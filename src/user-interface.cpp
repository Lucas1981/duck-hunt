#include "user-interface.h"
#include <stddef.h>      // for size_t
#include <sstream>       // for basic_stringstream, basic_ostream, stringstream
#include <string>        // for allocator, basic_string, char_traits
#include <vector>        // for vector
#include "animations.h"  // for AnimationIndex
#include "animator.h"    // for Animator
#include "state.h"       // for GameState, GameStateType
#include "text.h"        // for Text, TextAlignment

UserInterface::UserInterface(
    GameState* _gameState, Animator& _animator, Text& _text
) : animator(_animator), gameState(_gameState), text(_text) {
}

UserInterface::~UserInterface() {}

void UserInterface::draw(sf::RenderTarget& target) {
    drawBullets(target);
    drawTally(target);
    drawScore(target);
}

void UserInterface::drawBullets(sf::RenderTarget& target) {
    text.drawText(target, "shot", BULLETS_OFFSET_X, TEXT_OFFSET_Y, TextAlignment::LEFT);
    for (int i = 0; i < gameState->getBullets(); i++) {
        animator.draw(
            target,
            static_cast<float>(BULLETS_OFFSET_X + (i * 32)),
            VALUES_OFFSET_Y,
            Animations::AnimationIndex::BULLET,
            0
        );
    }
}

void UserInterface::drawTally(sf::RenderTarget& target) {
    const auto& duckAuditStates = gameState->getDuckAuditStates();

    text.drawText(target, "hit", DUCKS_OFFSET_X, TEXT_OFFSET_Y, TextAlignment::LEFT);
    for (size_t i = 0; i < 10; i++) {
        Animations::AnimationIndex animationIndex = 
            Animations::AnimationIndex::WHITE_DUCK;

        if (
            gameState->getState() == GameStateType::RUNNING &&
            gameState->getDuckAuditIndex() == i
        ) {
            animationIndex = Animations::AnimationIndex::FLICKER_DUCK;
        } else if (duckAuditStates[i]) {
            animationIndex = Animations::AnimationIndex::RED_DUCK;
        }

        animator.draw(
            target,
            static_cast<float>(DUCKS_OFFSET_X + (i * 32)),
            VALUES_OFFSET_Y,
            animationIndex,
            gameState->getAnimationTime()
        );
    }
}

void UserInterface::drawScore(sf::RenderTarget& target) {
    text.drawText(target, "score", SCORE_TEXT_OFFSET_X, TEXT_OFFSET_Y, TextAlignment::LEFT);
    std::stringstream score;
    score << gameState->getScore();
    text.drawText(target, score.str(), SCORE_VALUE_OFFSET_X, SCORE_VALUE_OFFSET_Y, TextAlignment::RIGHT);
}