#include "Shop.h"
#include <fstream>
#include <iostream>

// Funkcje które pozwalają zarządzać daną klasą
Shop::Shop(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font arial.ttf" << std::endl;
    }

    // Ładowanie tekstur piłki
    sf::Texture texture;
    std::vector<std::string> textureFiles = {"ball1.png", "ball2.png", "ball3.png", "ball4.png", "ball5.png"};
    for (const auto& file : textureFiles) {
        if (texture.loadFromFile(file)) {
            ballTextures.push_back(texture);
        } else {
            std::cerr << "Error opening textures files" << std::endl;
        }
    }

    // Inicjalizacja przedmiotów w sklepie
    for (int i = 0; i < int(ballTextures.size()); ++i) {
        sf::Text itemText;
        itemText.setFont(font);
        itemText.setFillColor(sf::Color::White);
        itemText.setString("Ball " + std::to_string(i + 1) + " - " + std::to_string(ballPrices[i]) + " coins");
        itemText.setPosition(sf::Vector2f(width / 3.f, height / (ballTextures.size() + 1) * (i + 1)));
        shopItems.push_back(itemText);
    }

    shopItems[0].setFillColor(sf::Color::Red);
    selectedItemIndex = 0;
}

void Shop::draw(sf::RenderWindow &window) {
    for (const auto &item : shopItems) {
        window.draw(item);
    }
    for(int i=0;i<5;i++)
    {
        ballsprite[i].setTexture(ballTextures[i]);
        ballsprite[i].setPosition(sf::Vector2f(1000.f,( 972.f / (ballTextures.size() + 1) * (i + 1))-25.f));
        float originalWidth = ballTextures[i].getSize().x;
        float originalHeight = ballTextures[i].getSize().y;
        ballsprite[i].setScale(80.f/originalWidth,80.f/originalHeight);
        window.draw(ballsprite[i]);
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
    if (selectedItemIndex + 1 < int(shopItems.size())) {
        shopItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        shopItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

sf::Texture& Shop::getSelectedTexture() {
    return ballTextures.at(selectedItemIndex);
}
int Shop::readCoins() {
    std::ifstream file("coins.txt");
    if (file.is_open()) {
        int coins;
        file >> coins;
        file.close();
        return coins;
    } else {
        std::cerr << "Error opening coins file" << std::endl;
        return 0;
    }
}
void Shop::updateCoins(int newBalance) {
    std::ofstream file("coins.txt");
    if (file.is_open()) {
        file << newBalance;
        file.close();
    } else {
        std::cerr << "Error opening coins file" << std::endl;
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
        sf::RenderWindow coinsWindow(sf::VideoMode(700, 500), "Settings");
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error: Could not load font arial.ttf" << std::endl;
        }
        coinsText.setFont(font);
        coinsText.setPosition(180,230);
        coinsText.setString("!NIE MASZ WYSTARCZAJACO PIENIEDZY!");

        bool inCoinstext=true;
        while (inCoinstext) {
            sf::Event event;
            while (coinsWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    inCoinstext = false;
                }else if (event.type == sf::Event::KeyPressed) {
                   inCoinstext = false;
                }

            coinsWindow.clear();
            coinsWindow.draw(coinsText);
            coinsWindow.display();
            }
        }

        return false;
    }
}
