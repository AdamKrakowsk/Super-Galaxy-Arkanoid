#ifndef BLOCK_H
#define BLOCK_H
#include "Object.h"
#include <SFML/Graphics.hpp>
#pragma once

class Block : public Object
{
public:
    Block(float width, float height, sf::Color color, int hp);
    void draw(sf::RenderWindow& window) const override;
    void update(float dt) override;
    void setHP(int hp);
    int getHP() const;
    bool isDestroyed() const override;
    void takeDamage() override;
    sf::FloatRect getBounds() const override;
    void setPosition(float x, float y);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

     void changeColor();

private:
    int m_hp;
    sf::RectangleShape m_shape;

};

#endif // BLOCK_H
