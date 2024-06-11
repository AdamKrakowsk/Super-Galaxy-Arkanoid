#ifndef SHOP_H
#define SHOP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Shop {
public:
    // Deklaracja funkcji i zmiennych
    Shop(float width, float height);
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const { return selectedItemIndex; }
    sf::Texture& getSelectedTexture();
    sf::Sprite& getaniamatedsprite();
    std::vector<int> ballPrices = {100, 250, 500, 500, 1000};
    int readCoins();
    void updateCoins(int newBalance);
    void animation(sf::RenderWindow &window);
    bool purchaseBall();
    sf::Texture arrayOfTexture[9];
    sf::Sprite animatedBall;
    sf::Sprite animatedSprite;

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> shopItems;
    std::vector<sf::Texture> ballTextures;
    sf::Sprite ballsprite[6];
    sf::Text coinsText;
    std::vector<sf::Texture> animatedTextures;
    sf::Clock animationClock;
    int animationFrame;

    void updateAnimation();
};

#endif // SHOP_H
