#include "Timer.h"
// Funkcje które pozwalają zarządzać daną klasą

Timer::Timer() {
    if (!m_font.loadFromFile("arial.ttf")) {
        // Obsługa błędu ładowania czcionki
    }

}

// restart czasu
void Timer::restart() {
    m_clock.restart();
}

void Timer::update() {
    sf::Time elapsed = m_clock.getElapsedTime();
    int seconds = static_cast<int>(elapsed.asSeconds());
    m_text.setString("Time: " + std::to_string(seconds));
}

void Timer::draw(sf::RenderWindow& window) {
    window.draw(m_text);
}
