#ifndef PADDLE_H
#define PADDLE_H
#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class Paddle : public Object
{
public:
    // Deklaracja funkcji i zmiennych
    Paddle(const sf::Texture& texture);
    void setSize(float width, float height);
    void draw(sf::RenderWindow& window) const override;
    void update(float dt) override;
    bool isDestroyed() const override { return false; }
    void takeDamage() override {}
    sf::FloatRect getBounds() const override;
    void setPosition(float x, float y);
    void begin(sf::Texture& texture);
private:
    sf::Sprite m_sprite;


};

#endif // PADDLE_H
