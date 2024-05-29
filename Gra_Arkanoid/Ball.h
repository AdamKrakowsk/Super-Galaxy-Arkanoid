#ifndef BALL_H
#define BALL_H
#include "Object.h"


class Ball : public Object
{
public:
    Ball(const sf::Texture& texture);

    void update(sf::Time deltaTime);
    void setVelocity(const sf::Vector2f& velocity);
    const sf::Vector2f& getVelocity() const;

private:
    sf::Vector2f mVelocity;


};

#endif // BALL_H
