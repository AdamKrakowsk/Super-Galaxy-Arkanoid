#include "SoundManager.h"
#include <iostream>
SoundManager::SoundManager() {}
void SoundManager::Soundtrack_play(){
    if (!soundtrack_buffer.loadFromFile("soundtrack.wav")) {
        std::cerr << "Error: Could not load background.png" << std::endl;
        return;
    }
    soundtrack.setBuffer(soundtrack_buffer);
    soundtrack.setVolume(5);
    soundtrack.play();
}
void SoundManager::collision_sound(){
if (!koliz_buffer.loadFromFile("kol.wav")) {
    std::cerr << "Error: Could not load background.png" << std::endl;
    return;
}

koliz.setBuffer(koliz_buffer);
koliz.setVolume(10);
koliz.play();
}
