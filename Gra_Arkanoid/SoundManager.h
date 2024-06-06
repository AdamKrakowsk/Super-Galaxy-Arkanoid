#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SoundManager
{
public:
    // Deklaracja funkcji i zmiennych
    SoundManager();
    sf::SoundBuffer koliz_buffer;
    sf::Sound koliz;
    sf::SoundBuffer soundtrack_buffer;
    sf::Sound soundtrack;
    void Soundtrack_play();
    void collision_sound();
    void setSoundtrackVolume(int sv);
    void setCollisionVolume(int hv);
};

#endif // SOUNDMANAGER_H
