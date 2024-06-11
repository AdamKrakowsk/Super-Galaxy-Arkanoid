#ifndef HEARTSYSTEM_H
#define HEARTSYSTEM_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class HeartSystem {
public:
    // Deklaracja funkcji i zmiennych
    HeartSystem(int initialHearts, const sf::Texture& heartTexture, float x, float y);
    void draw(sf::RenderWindow& window);
    void loseHeart();
    bool hasHearts() const;

private:
    std::vector<sf::Sprite> m_hearts;
    int m_initialHearts;
    float m_x, m_y;
};

#endif // HEARTSYSTEM_H
