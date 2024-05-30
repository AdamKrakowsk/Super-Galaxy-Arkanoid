#ifndef BONUS_H
#define BONUS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bonus
{
public:
    Bonus();
    void createBonus();
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;
    bool isCaught() const;
    void catchBonus();

private:
    sf::Texture m_bonusTexture;
    sf::Sprite m_bonusSprite;
    sf::Vector2f m_velocity;
    bool m_caught;
    float m_speed;
};

#endif // BONUS_H

