#ifndef PADDLE_H
#define PADDLE_H

#include "Object.h"

class Paddle : public Object
{
public:
    Paddle(const sf::Texture& texture);
    void setSize(float width, float height);
};

#endif // PADDLE_H
