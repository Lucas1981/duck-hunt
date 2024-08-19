#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio/Sound.hpp>        // for Sound
#include <SFML/Audio/SoundBuffer.hpp>  // for SoundBuffer
#include <queue>                       // for queue
#include <unordered_map>               // for unordered_map
#include <list>

// Enum representing different sound effects
enum class SoundEffect {
    TITLE_SCREEN,
    NEW_LEVEL,
    SHOOT,
    QUACK_FLY,
    QUACK_SHOT,
    FALL,
    DROP,
    TALLY,
    GAME_OVER,
    ROUND_BEAT,
    GAME_WON,
};

class Sound {
public:
    Sound();
    ~Sound();

    void enqueue(SoundEffect soundEffect);
    void handleQueue();
    void stopAll();

private:
    void loadSounds();
    std::unordered_map<SoundEffect, sf::SoundBuffer> soundBuffers;
    std::queue<sf::Sound> soundQueue;
    std::list<sf::Sound> activeSounds;  // To keep track of currently playing sounds
};

#endif // SOUND_H
