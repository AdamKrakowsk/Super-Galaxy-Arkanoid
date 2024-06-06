#include "Highscore.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
// Funkcje które pozwalają zarządzać daną klasą

Highscore::Highscore() : m_highscore() {
    loadHighscore();
}

int Highscore::getHighscore() const {
    return m_highscore;
}

void Highscore::draw(sf::RenderWindow& window) const {

}


// funkcja sprawdzająca Highscore
void Highscore::setHighscore(int highscore) {
    if (highscore < m_highscore) {
        m_highscore = highscore;
    }
}

// Zapis do pliku wyniku
void Highscore::saveHighscore() {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << m_highscore;
        file.close();
    } else {
        std::cerr << "Error: Could not open highscore.txt for writing" << std::endl;
    }
}

// wczytywanie z pliku wyniku
void Highscore::loadHighscore() {
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> m_highscore;
        file.close();
    } else {
        std::cerr << "Error: Could not open highscore.txt for reading" << std::endl;
    }
}

