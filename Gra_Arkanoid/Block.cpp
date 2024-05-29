#include "Block.h"

Block::Block(float width, float height, const sf::Color& color, int hp)
    : Object(sf::Texture()), mHP(hp), mShape(sf::Vector2f(width, height)) {
    mShape.setFillColor(color);
    mWidth = width;
    mHeight = height;
}

void Block::setHP(int hp) {
    mHP = hp;
}

int Block::getHP() const {
    return mHP;
}

void Block::takeDamage(int damage) {
    mHP -= damage;
    if (mHP < 0) {
        mHP = 0;
    }
}

bool Block::isDestroyed() const {
    return mHP <= 0;
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform(); // Apply the object's transform
    target.draw(mShape, states);
}
