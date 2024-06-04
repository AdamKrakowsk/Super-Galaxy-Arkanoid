#include "SoundManager.h"
#include <iostream>
SoundManager::SoundManager() {}
void SoundManager::Soundtrack_play(){
    if (!soundtrack_buffer.loadFromFile("soundtrack.wav")) {
        std::cerr << "Error: Could not load background.png" << std::endl;
        return;
    }
    soundtrack.setBuffer(soundtrack_buffer);
    soundtrack.play();
}
void SoundManager::collision_sound(){
    if (!koliz_buffer.loadFromFile("kol.wav")) {
        std::cerr << "Error: Could not load background.png" << std::endl;
        return;
    }
koliz.setBuffer(koliz_buffer);
koliz.play();
}
void SoundManager::setSoundtrackVolume(int sv){
    soundtrack.setVolume(sv);
}
void SoundManager::setCollisionVolume(int hv){
    koliz.setVolume(hv);
}
