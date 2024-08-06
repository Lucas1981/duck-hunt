#include "user-interface.h"
#include <sstream>       // for basic_stringstream, basic_ostream, stringstream
#include <string>        // for allocator, basic_string, char_traits
#include "animations.h"  // for AnimationIndex
#include "animator.h"    // for Animator
#include "state.h"       // for GameState
#include "text.h"        // for Text, TextAlignment

UserInterface::UserInterface(
    GameState* _gameState, Animator& _animator, Text& _text
) : animator(_animator), gameState(_gameState), text(_text) {}

UserInterface::~UserInterface() {}

void UserInterface::draw(sf::RenderTarget& target) {
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

    text.drawText(target, "hit", DUCKS_OFFSET_X, TEXT_OFFSET_Y, TextAlignment::LEFT);
    for (int i = 0; i < gameState->getDucksShot(); i++) {
        animator.draw(
            target,
            static_cast<float>(DUCKS_OFFSET_X + (i * 32)),
            VALUES_OFFSET_Y,
            Animations::AnimationIndex::RED_DUCK,
            0
        );
    }

    text.drawText(target, "score", SCORE_TEXT_OFFSET_X, TEXT_OFFSET_Y, TextAlignment::LEFT);
    std::stringstream score;
    score << gameState->getScore();
    text.drawText(target, score.str(), SCORE_VALUE_OFFSET_X, SCORE_VALUE_OFFSET_Y, TextAlignment::RIGHT);
}