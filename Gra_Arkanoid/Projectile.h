#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(float x, float y);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    float m_speed;
};

#endif // PROJECTILE_H
