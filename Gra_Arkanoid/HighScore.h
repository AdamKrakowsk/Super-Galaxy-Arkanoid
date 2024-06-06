// highscore.h
#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Highscore {
public:
    // Deklaracja funkcji i zmiennych
    Highscore();

    // Metody do zarządzania highscore
    int getHighscore() const;
    void setHighscore(int highscore);
    void draw(sf::RenderWindow& window) const;


    void saveHighscore();
    void loadHighscore();

private:
    int m_highscore;
};

#endif // HIGHSCORE_H
