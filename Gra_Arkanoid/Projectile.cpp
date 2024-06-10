#include "Projectile.h"
#include <iostream>

Projectile::Projectile(float x, float y)
    : m_speed(1300.0f) {
    if (!m_texture.loadFromFile("projectile.png")) {
        std::cerr << "Error: Could not load projectile.png" << std::endl;
        return;
    }
    m_sprite.setTexture(m_texture);


    m_sprite.setScale(0.05f, 0.05f);

    m_sprite.setPosition(x, y);
}

void Projectile::update(sf::Time deltaTime) {
    m_sprite.move(0, -m_speed * deltaTime.asSeconds());
}

void Projectile::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

sf::FloatRect Projectile::getBounds() const {
    return m_sprite.getGlobalBounds();
}
