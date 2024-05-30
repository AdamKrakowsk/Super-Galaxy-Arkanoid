#include "Paddle.h"

Paddle::Paddle(const sf::Texture& texture): Object(texture)
{
    // Ustawienie domyślnego rozmiaru paletki
    //setSize(150.f, 30.f);
}

void Paddle::setSize(float width, float height) {
     Object::setSize(width, height);
}

void Paddle::begin(sf::Texture& texture)
{
     m_sprite.setTexture(texture);
}

void Paddle::draw(sf::RenderWindow& window) const{

    window.draw(m_sprite);
}

void Paddle::update(float dt) {
    // Aktualizacja ruchu paletki odbywa się w funkcji Game::update
}

sf::FloatRect Paddle::getBounds() const {
    return m_sprite.getGlobalBounds();
}

void Paddle::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}
