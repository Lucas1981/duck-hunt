#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio/Sound.hpp>        // for Sound
#include <SFML/Audio/SoundBuffer.hpp>  // for SoundBuffer
#include <queue>                       // for queue
#include <unordered_map>               // for unordered_map
#include <list>

// Enum representing different sound effects
enum class SoundEffect {
    SHOOT,
    QUACK,
    MISS,
    // Add other sound effects here
};

class Sound {
public:
    Sound();
    ~Sound();

    void enqueue(SoundEffect soundEffect);
    void handleQueue();

private:
    void loadSounds();
    std::unordered_map<SoundEffect, sf::SoundBuffer> soundBuffers;
    std::queue<sf::Sound> soundQueue;
    std::list<sf::Sound> activeSounds;  // To keep track of currently playing sounds
};

#endif // SOUND_H
