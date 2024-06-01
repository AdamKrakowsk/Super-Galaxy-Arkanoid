#include "bonus.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
Bonus::Bonus()
    : m_isCaught(false), m_velocity(0.f, 200.f), m_type(SpeedUp) {}

void Bonus::createBonus() {

}

void Bonus::setTexture(const sf::Texture& texture) {
    m_sprite.setTexture(texture);
    float originalWidth = texture.getSize().x;
    float originalHeight = texture.getSize().y;

    float desiredWidth = 70.f;
    float desiredHeight = 40.f;

    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;
    m_sprite.setScale(scaleX, scaleY);
    m_speed = 400.0f;
}

void Bonus::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

void Bonus::update(sf::Time deltaTime) {
    if (!m_isCaught) {
        m_sprite.move(0.f, m_velocity.y * deltaTime.asSeconds());
    }
}

void Bonus::render(sf::RenderWindow& window) {
    if (!m_isCaught) {
        window.draw(m_sprite);
    }
}

bool Bonus::isCaught() const {
    return m_isCaught;
}

void Bonus::catchBonus() {
    m_isCaught = true;
}

sf::FloatRect Bonus::getBounds() const {
    return m_sprite.getGlobalBounds();
}
Bonus::Type Bonus::getType() const {
    return m_type;
}
void Bonus::setType(Type type) {
    m_type = type;
}
