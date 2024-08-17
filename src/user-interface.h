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
    void drawBullets(sf::RenderTarget& target);
    void drawTally(sf::RenderTarget& target);
    void drawScore(sf::RenderTarget& target);

    static constexpr float BULLETS_OFFSET_X = UNIT_SIZE + 94;
    static constexpr float DUCKS_TEXT_OFFSET_X = UNIT_SIZE + 304;
    static constexpr float DUCKS_ICONS_OFFSET_X = UNIT_SIZE + 364;
    static constexpr float DUCKS_OFFSET_Y = UNIT_SIZE + 678;
    static constexpr float TARGET_OFFSET_Y = DUCKS_OFFSET_Y + 32;
    static constexpr float VALUES_OFFSET_Y = UNIT_SIZE + 670 + 38;
    static constexpr float TEXT_OFFSET_Y = UNIT_SIZE + 670;
    static constexpr float SCORE_TEXT_OFFSET_X = UNIT_SIZE + 800;
    static constexpr float SCORE_VALUE_OFFSET_X = SCORE_TEXT_OFFSET_X + 122;
    static constexpr float SCORE_VALUE_OFFSET_Y = VALUES_OFFSET_Y;
    Animator& animator;
    GameState* gameState;
    Text& text;
};

#endif