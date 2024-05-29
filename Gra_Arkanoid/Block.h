#ifndef BLOCK_H
#define BLOCK_H
#include "Object.h"
#include <SFML/Graphics.hpp>

class Block : public Object
{
public:
    Block(float width, float height, const sf::Color& color, int hp);
    void setHP(int hp);
    int getHP() const;
    void takeDamage(int damage);
    bool isDestroyed() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    int mHP;
    sf::RectangleShape mShape;

};

#endif // BLOCK_H
