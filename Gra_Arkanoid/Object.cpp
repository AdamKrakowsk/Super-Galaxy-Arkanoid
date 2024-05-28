#include "Object.h"

Object::Object(const sf::Texture& texture) : sf::Sprite(texture), mWidth(0), mHeight(0) {}

void Object::setSize(float width, float height) {
    mWidth = width;
    mHeight = height;

    // Skalowanie sprite'a zgodnie z nowymi wymiarami
    if (const sf::Texture* texture = getTexture()) {
        sf::Vector2u textureSize = texture->getSize();
        setScale(
            width / static_cast<float>(textureSize.x),
            height / static_cast<float>(textureSize.y)
            );
    }
}

bool Object::checkCollision(const Object& other) const {
    return getGlobalBounds().intersects(other.getGlobalBounds());
}

// float Object::getWidth()  {
//     return mWidth;
// }

// float Object::getHeight()  {
//     return mHeight;
// }
