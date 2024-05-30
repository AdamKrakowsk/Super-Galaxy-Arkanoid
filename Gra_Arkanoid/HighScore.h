// highscore.h
#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Highscore {
public:
    Highscore(); // Konstruktor

    // Metody do zarządzania highscore
    int getHighscore() const; // Pobierz aktualny highscore
    void setHighscore(int newHighscore); // Ustaw nowy highscore
    void draw(sf::RenderWindow& window) const;


    void saveToFile(const std::string& filename); // Zapisz highscore do pliku
    void loadFromFile(const std::string& filename); // Wczytaj highscore z pliku

private:
    int m_highscore;
};

#endif // HIGHSCORE_H
