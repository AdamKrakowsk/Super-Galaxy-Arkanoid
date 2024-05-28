#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>


class Object : public sf::Sprite
{
public:
    Object(const sf::Texture& texture);
    void setSize(float width, float height);
    bool checkCollision(const Object& other) const;

    float getWidth() ;
    float getHeight() ;

private:
    float mWidth;
    float mHeight;

};

#endif // OBJECT_H
