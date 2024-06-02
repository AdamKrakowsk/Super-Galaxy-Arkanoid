#ifndef BONUS_H
#define BONUS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bonus {
public:
    enum Type {
        SpeedUp,
        PaddleEnlarge,
        ExtraCoins,
        PaddleSpeedUp
    };


    Bonus();

    void createBonus();
    void setPosition(float x, float y);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);
    bool isCaught() const;
    void catchBonus();
    sf::FloatRect getBounds() const;

    void setTexture(const sf::Texture& texture);
    Type getType() const; // metoda getType(), która zwraca typ bonusu
    void setType(Type type); // metoda do ustawiania typu bonusu

private:
    sf::Sprite m_sprite;
    bool m_isCaught;
    float m_speed;
    sf::Vector2f m_velocity;
    Type m_type;
};


#endif // BONUS_H
