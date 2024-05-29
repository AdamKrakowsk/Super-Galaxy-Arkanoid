#include "Ball.h"

Ball::Ball(const sf::Texture& texture) : Object(texture), mVelocity(0.f, 0.f) {}

// void Ball::update(sf::Time deltaTime) {
//     move(mVelocity * deltaTime.asSeconds());

//     // Sprawdzenie kolizji z granicami okna
//     sf::FloatRect bounds = getGlobalBounds();
//     if (bounds.left < 0 || bounds.left + bounds.width > 1728) {
//         mVelocity.x = -mVelocity.x;
//     }
//     if (bounds.top < 0 || bounds.top + bounds.height > 972) {
//         mVelocity.y = -mVelocity.y;
//     }
// }

void Ball::setVelocity(const sf::Vector2f& velocity) {
    mVelocity = velocity;
}

const sf::Vector2f& Ball::getVelocity() const {
    return mVelocity;
}
