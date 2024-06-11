#include "Block.h"
// Funkcje które pozwalają zarządzać daną klasą

// konstruktor z danymi
Block::Block(float width, float height, sf::Color color, int hp)
    : m_hp(hp) {
    m_shape.setSize(sf::Vector2f(width, height));
    m_shape.setFillColor(color);
}

void Block::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
}

void Block::update(float dt) {

}


void Block::setHP(int hp) {
    m_hp = hp;
}

int Block::getHP() const {
    return m_hp;
}
// funkcja odbierająca HP
void Block::takeDamage() {
    if (m_hp > 0) {
        --m_hp;
    }
    changeColor();  // Zmiana koloru po otrzymaniu obrażeń
}


// funkcja do zmiany koloru
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
// funckja sprawdzająca zniszczenie
bool Block::isDestroyed() const {
    return m_hp <= 0;
}
void Block::setPosition(float x, float y) {
    m_shape.setPosition(x, y);
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_shape, states);
}
