#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>


class Object : public sf::Sprite
{
public:

    Object(const sf::Texture&);
    Object();
    void setSize(float width, float height);
    bool checkCollision(const Object& other) const;

    float getWidth() ;
    float getHeight() ;

    virtual ~Object() = default;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void update(float dt) = 0;
    virtual bool isDestroyed() const = 0; // Deklaracja wirtualnej funkcji
    virtual void takeDamage() = 0;        // Deklaracja wirtualnej funkcji
    virtual sf::FloatRect getBounds() const = 0; // Deklaracja funkcji zwracającej granice obiektu


protected:
    float mWidth;
    float mHeight;

};

#endif // OBJECT_H
