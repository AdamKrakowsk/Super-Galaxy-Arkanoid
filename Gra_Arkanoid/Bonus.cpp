#include "Bonus.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Bonus::Bonus() {}

void Bonus::createBonus() {
    if (!m_bonusTexture.loadFromFile("bonus.png")) {
        std::cerr << "Error: Could not load bonus.png" << std::endl;  // Poprawiony komunikat błędu
        return;
    }
    m_bonusSprite.setTexture(m_bonusTexture);
    float originalWidth = m_bonusTexture.getSize().x;
    float originalHeight = m_bonusTexture.getSize().y;

    float desiredWidth = 30.f;
    float desiredHeight = 30.f;

    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;
    m_speed = 100.0f;
    m_bonusSprite.setScale(scaleX, scaleY);
    m_bonusSprite.setPosition(500, 400);
}

void Bonus::setPosition(float x, float y) {
    m_bonusSprite.setPosition(x, y);
}

void Bonus::update(sf::Time deltaTime) {
    m_bonusSprite.move(0, m_speed * deltaTime.asSeconds());
}

void Bonus::render(sf::RenderWindow& window) {
    window.draw(m_bonusSprite);
}

sf::FloatRect Bonus::getBounds() const {
    return m_bonusSprite.getGlobalBounds();
}

bool Bonus::isCaught() const {
    return m_caught;
}

void Bonus::catchBonus() {
    m_caught = true;
}
