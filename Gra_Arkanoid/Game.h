#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow mWindow;

};

#endif // GAME_H
