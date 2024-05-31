#ifndef BONUS_H
#define BONUS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bonus {
public:
    Bonus();

    void createBonus();
    void setPosition(float x, float y);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);
    bool isCaught() const;
    void catchBonus();
    sf::FloatRect getBounds() const;

    void setTexture(const sf::Texture& texture);

private:
    sf::Sprite m_sprite;
    bool m_isCaught;
    float m_speed;
    sf::Vector2f m_velocity;
};


#endif // BONUS_H
