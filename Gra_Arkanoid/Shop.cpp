#include "Shop.h"
#include <fstream>
// Funkcje które pozwalają zarządzać daną klasą
Shop::Shop(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        // Obsługa błedu
    }

    // Ładowanie tekstur piłki
    sf::Texture texture;
    std::vector<std::string> textureFiles = {"ball1.png", "ball2.png", "ball3.png", "ball4.png", "ball5.png"};
    for (const auto& file : textureFiles) {
        if (texture.loadFromFile(file)) {
            ballTextures.push_back(texture);
        } else {
            // Obsługa błedu
        }
    }

    // Inicjalizacja przedmiotów w sklepie
    for (int i = 0; i < ballTextures.size(); ++i) {
        sf::Text itemText;
        itemText.setFont(font);
        itemText.setFillColor(sf::Color::White);
        itemText.setString("Ball " + std::to_string(i + 1) + " - " + std::to_string(ballPrices[i]) + " coins");
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

// obsługa poruszania się po sklepie
void Shop::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        shopItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        shopItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

// obsługa poruszania się po sklepie
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
int Shop::readCoins() {
    std::ifstream file("coins.txt");
    if (file.is_open()) {
        int coins;
        file >> coins;
        file.close();
        return coins;
    } else {
        // Handle file opening error
        return 0;
    }
}
void Shop::updateCoins(int newBalance) {
    std::ofstream file("coins.txt");
    if (file.is_open()) {
        file << newBalance;
        file.close();
    } else {
        // Handle file opening error
    }
}
bool Shop::purchaseBall() {
    int coins = readCoins();
    int ballPrice = ballPrices[selectedItemIndex];
    if (coins >= ballPrice) {
        int newBalance = coins - ballPrice;
        updateCoins(newBalance);
        // Add the purchased ball's texture to the game or perform any other necessary actions
        return true;
    } else {
        // Insufficient coins
        return false;
    }
}
