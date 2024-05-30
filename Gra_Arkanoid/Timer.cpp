#include "Timer.h"

Timer::Timer() {
    if (!m_font.loadFromFile("arial.ttf")) {
        // Obsługa błędu ładowania czcionki
    }
    // m_text.setFont(m_font);
    // m_text.setCharacterSize(50);
    // m_text.setFillColor(sf::Color::White);
    // m_text.setPosition(750, 10); // Ustaw górę na środku
}

void Timer::restart() {
    m_clock.restart();
}

void Timer::update() {
    sf::Time elapsed = m_clock.getElapsedTime();
    int seconds = static_cast<int>(elapsed.asSeconds());
    m_text.setString("Czas: " + std::to_string(seconds));
}

void Timer::draw(sf::RenderWindow& window) {
    window.draw(m_text);
}
