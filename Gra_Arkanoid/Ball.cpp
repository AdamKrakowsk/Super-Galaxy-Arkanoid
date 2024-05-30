#include "Ball.h"

Ball::Ball(sf::Texture& texture) : m_sprite(texture), m_speed(300.0f) {
    m_sprite.setScale(0.1f, 0.1f); // Skalowanie piłki, jeśli jest zbyt duża
    mVelocity = sf::Vector2f(-m_speed, -m_speed);
}

void Ball::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void Ball::update(float dt) {
    m_sprite.move(mVelocity * dt);

    sf::FloatRect bounds = m_sprite.getGlobalBounds();

    if (bounds.left <= 0 || bounds.left + bounds.width >= 1728) {
        mVelocity.x = -mVelocity.x;
    }

    if (bounds.top <= 0) {
        mVelocity.y = -mVelocity.y;
    }
}

void Ball::handleCollision(Object& object) {
    if (m_sprite.getGlobalBounds().intersects(object.getBounds())) {
        mVelocity.y = -mVelocity.y;
        object.takeDamage();
    }
}

void Ball::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::FloatRect Ball::getBounds() const {
    return m_sprite.getGlobalBounds();
}

bool Ball::isDestroyed() const {
    return 1;
}

void Ball::takeDamage() {

}
