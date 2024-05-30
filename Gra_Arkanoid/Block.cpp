#include "Block.h"

Block::Block(float width, float height, sf::Color color, int hp)
    : m_hp(hp) {
    m_shape.setSize(sf::Vector2f(width, height));
    m_shape.setFillColor(color);
}

void Block::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
}

void Block::update(float dt) {
    // Bloki nie potrzebują aktualizacji co klatkę, chyba że mają jakieś animacje lub inne właściwości
}


void Block::setHP(int hp) {
    m_hp = hp;
}

int Block::getHP() const {
    return m_hp;
}

void Block::takeDamage() {
    if (m_hp > 0) {
        --m_hp;
    }
    changeColor();  // Zmiana koloru po otrzymaniu obrażeń
}



void Block::changeColor() {
    if (m_hp == 2) {
        m_shape.setFillColor(sf::Color::Green);
    } else if (m_hp == 1) {
        m_shape.setFillColor(sf::Color::Blue);
    } else if (m_hp <= 0) {
        m_shape.setFillColor(sf::Color::Transparent);
    }
}




sf::FloatRect Block::getBounds() const {
    return m_shape.getGlobalBounds();
}

bool Block::isDestroyed() const {
    return m_hp <= 0;
}
void Block::setPosition(float x, float y) {
    m_shape.setPosition(x, y);
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform(); // Apply the object's transform
    target.draw(m_shape, states);
}
