#include "sound.h"
#include <iostream>  // for basic_ostream, operator<<, endl, cerr, cout
#include <string>    // for char_traits, basic_string

Sound::Sound() {
    loadSounds();
}

Sound::~Sound() {
    std::cout << "Deconstructing\n";
    // The sound buffers and active sounds will be automatically destroyed
}

void Sound::loadSounds() {
    // Load each sound buffer and store it in the map with its corresponding enum value
    if (!soundBuffers[SoundEffect::SHOOT].loadFromFile("../assets/gunshot.wav")) {
        std::cerr << "Failed to load gunshot.wav" << std::endl;
    }

    if (!soundBuffers[SoundEffect::QUACK].loadFromFile("../assets/quack.wav")) {
        std::cerr << "Failed to load hit.wav" << std::endl;
    }

    if (!soundBuffers[SoundEffect::MISS].loadFromFile("../assets/miss.wav")) {
        std::cerr << "Failed to load miss.wav" << std::endl;
    }
}

void Sound::enqueue(SoundEffect soundEffect) {
    if (soundBuffers.find(soundEffect) != soundBuffers.end()) {
        sf::Sound sound;
        sound.setBuffer(soundBuffers[soundEffect]);
        soundQueue.push(sound);
    } else {
        std::cerr << "Sound effect not found" << std::endl;
    }
}

void Sound::handleQueue() {
    // Move sounds from queue to active sounds and start playing them
    while (!soundQueue.empty()) {
        activeSounds.push_back(soundQueue.front());  // Store the sound to ensure it remains in scope
        activeSounds.back().play();  // Play the last added sound
        soundQueue.pop();
    }

    // Remove sounds that have finished playing
    for (auto it = activeSounds.begin(); it != activeSounds.end(); ) {
        if (it->getStatus() == sf::Sound::Stopped) {
            it = activeSounds.erase(it); // Safely erase while iterating
        } else {
            ++it;
        }
    }
}

