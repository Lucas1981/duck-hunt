#ifndef USER_INTERFACE
#define USER_INTERFACE

#include "constants.h"  // for UNIT_SIZE
class Animator;
class GameState;
namespace sf { class RenderTarget; }  // lines 7-7

using namespace Constants;

class UserInterface {
public:
    UserInterface(GameState* _gameState, Animator& _animator);
    ~UserInterface();
    void draw(sf::RenderTarget& target);

private:
    static constexpr float bulletsOffsetX = UNIT_SIZE + 64;
    static constexpr float ducksOffsetX = UNIT_SIZE + 224;
    static constexpr float offsetY = UNIT_SIZE + 512;
    Animator& animator;
    GameState* gameState;
};

#endif