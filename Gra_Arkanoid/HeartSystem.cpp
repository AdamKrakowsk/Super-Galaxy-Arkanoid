#include "HeartSystem.h"

// Funkcje które pozwalają zarządzać daną klasą
HeartSystem::HeartSystem(int initialHearts, const sf::Texture& heartTexture, float x, float y)
    : m_initialHearts(initialHearts), m_x(x), m_y(y)
{
    for (int i = 0; i < initialHearts; ++i) {
        sf::Sprite heart;
        heart.setTexture(heartTexture);
        heart.setPosition(x + i * 40, y);
        m_hearts.push_back(heart);
    }
}

void HeartSystem::draw(sf::RenderWindow& window) {
    for (const auto& heart : m_hearts) {
        window.draw(heart);
    }
}

void HeartSystem::loseHeart() {
    if (!m_hearts.empty()) {
        m_hearts.pop_back();
    }
}

bool HeartSystem::hasHearts() const {
    return !m_hearts.empty();
}
