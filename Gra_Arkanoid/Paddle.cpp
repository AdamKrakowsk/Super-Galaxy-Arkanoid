#include "Paddle.h"

Paddle::Paddle(const sf::Texture& texture): Object(texture)
{
    // Ustawienie domyślnego rozmiaru paletki
    setSize(150.f, 30.f);
}

void Paddle::setSize(float width, float height) {
    Object::setSize(width, height);
}

