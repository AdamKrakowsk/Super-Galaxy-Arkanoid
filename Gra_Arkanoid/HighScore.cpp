#include "Highscore.h"
#include <fstream>
#include <SFML/Graphics.hpp>

Highscore::Highscore() : m_highscore(0) {}

int Highscore::getHighscore() const {
    return m_highscore;
}

void Highscore::draw(sf::RenderWindow& window) const {
    // Logika rysowania highscore na ekranie
}



void Highscore::setHighscore(int newHighscore) {
    m_highscore = newHighscore;
}

void Highscore::saveToFile(const std::string& filename) {
    std::ofstream file(filename.c_str()); // poprawna inicjalizacja obiektu plikowego
    if (file.is_open()) {
        file << m_highscore;
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}

void Highscore::loadFromFile(const std::string& filename) {
    std::ifstream file(filename.c_str()); // poprawna inicjalizacja obiektu plikowego
    if (file.is_open()) {
        file >> m_highscore;
        file.close();
    } else {
        std::cerr << "Error: Could not open file for reading." << std::endl;
    }
}

