#ifndef USER_INTERFACE
#define USER_INTERFACE

#include "constants.h"  // for UNIT_SIZE
class Animator;
class GameState;
class Text;
namespace sf { class RenderTarget; }  // lines 7-7

using namespace Constants;

class UserInterface {
public:
    UserInterface(GameState* _gameState, Animator& _animator, Text& _text);
    ~UserInterface();
    void draw(sf::RenderTarget& target);

private:
    static constexpr float BULLETS_OFFSET_X = UNIT_SIZE + 64;
    static constexpr float DUCKS_OFFSET_X = UNIT_SIZE + 224;
    static constexpr float VALUES_OFFSET_Y = UNIT_SIZE + 512;
    static constexpr float TEXT_OFFSET_Y = UNIT_SIZE + 512 - 38;
    static constexpr float SCORE_TEXT_OFFSET_X = UNIT_SIZE + 608;
    static constexpr float SCORE_VALUE_OFFSET_X = SCORE_TEXT_OFFSET_X + 122;
    static constexpr float SCORE_VALUE_OFFSET_Y = VALUES_OFFSET_Y - 4;
    Animator& animator;
    GameState* gameState;
    Text& text;
};

#endif