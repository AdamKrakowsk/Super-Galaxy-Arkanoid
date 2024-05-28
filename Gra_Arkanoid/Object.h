#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>


class Object : public sf::Sprite
{
public:
    Object(const sf::Texture& texture);
};

#endif // OBJECT_H
