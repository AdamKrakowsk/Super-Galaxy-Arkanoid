#ifndef SHOP_H
#define SHOP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Shop {
public:
    Shop(float width, float height);
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const { return selectedItemIndex; }
    sf::Texture& getSelectedTexture();

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> shopItems;
    std::vector<sf::Texture> ballTextures;
};

#endif // SHOP_H
