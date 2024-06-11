#ifndef BALL_H
#define BALL_H
#include "Object.h"
#pragma once
#include <SFML/Graphics.hpp>

class Ball : public Object
{
public:
    // Deklaracja funkcji i zmiennych
    Ball(sf::Texture& texture);

    void draw(sf::RenderWindow& window) const override;
    void update(float dt) override;

    void takeDamage() override;
    bool isDestroyed() const override;

    void handleCollision(Object& object);
    void setPosition(float x, float y);
    sf::FloatRect getBounds() const override;

private:
    sf::Vector2f mVelocity;
    sf::Sprite m_sprite;
    float m_speed;



};

#endif // BALL_H
