#include "Shop.h"

Shop::Shop(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
    }

    // Load ball textures
    sf::Texture texture;
    std::vector<std::string> textureFiles = {"ball1.png", "ball2.png", "ball3.png", "ball4.png", "ball5.png"};
    for (const auto& file : textureFiles) {
        if (texture.loadFromFile(file)) {
            ballTextures.push_back(texture);
        } else {
            // Handle error
        }
    }

    // Initialize shop items
    for (int i = 0; i < ballTextures.size(); ++i) {
        sf::Text itemText;
        itemText.setFont(font);
        itemText.setFillColor(sf::Color::White);
        itemText.setString("Ball " + std::to_string(i + 1));
        itemText.setPosition(sf::Vector2f(width / 2.f, height / (ballTextures.size() + 1) * (i + 1)));
        shopItems.push_back(itemText);
    }

    shopItems[0].setFillColor(sf::Color::Red);
    selectedItemIndex = 0;
}

void Shop::draw(sf::RenderWindow &window) {
    for (const auto &item : shopItems) {
        window.draw(item);
    }
}

void Shop::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        shopItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        shopItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Shop::moveDown() {
    if (selectedItemIndex + 1 < shopItems.size()) {
        shopItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        shopItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

sf::Texture& Shop::getSelectedTexture() {
    return ballTextures[selectedItemIndex];
}
