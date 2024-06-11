#include "Shop.h"
#include <fstream>
#include <iostream>

// Funkcje które pozwalają zarządzać daną klasą
Shop::Shop(float width, float height) : animationFrame(0) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font arial.ttf" << std::endl;
    }

    // Ładowanie tekstur piłki
    std::vector<std::string> textureFiles = {"buzkaball.png", "BIGMACball.png", "G.Sball.png", "minimajkball.png", "ball5.png"};
    for (const auto& file : textureFiles) {
        sf::Texture texture;
        if (texture.loadFromFile(file)) {
            ballTextures.push_back(texture);
        } else {
            std::cerr << "Error opening texture file: " << file << std::endl;
        }
    }

    // Inicjalizacja przedmiotów w sklepie
    for (int i = 0; i < int(ballTextures.size()); ++i) {
        sf::Text itemText;
        itemText.setFont(font);
        int coins = readCoins();
        if (coins >= ballPrices[i])
            itemText.setFillColor(sf::Color::Green);
        else
            itemText.setFillColor(sf::Color::Red);
        itemText.setString("Ball " + std::to_string(i + 1) + " - " + std::to_string(ballPrices[i]) + " coins");
        itemText.setPosition(sf::Vector2f(width / 3.f, height / (ballTextures.size() + 1) * (i + 1)));
        itemText.setCharacterSize(48);
        shopItems.push_back(itemText);
    }

    shopItems[0].setFillColor(sf::Color::Red);
    selectedItemIndex = 0;

    // ładowanie animowanej tekstury
    std::vector<std::string> animatedTextureFiles = {"specjal1ball.png", "specjal2ball.png", "specjal3ball.png", "specjal4ball.png", "specjal5ball.png"};
    for (const auto& file : animatedTextureFiles) {
        sf::Texture texture;
        if (texture.loadFromFile(file)) {
            animatedTextures.push_back(texture);
        } else {
            std::cerr << "Error opening animated texture file: " << file << std::endl;
        }
    }

    // Inicjalizacja Sprite animacji
    if (!animatedTextures.empty()) {
        animatedSprite.setTexture(animatedTextures[0]);
        animatedSprite.setPosition(1000.f,800.f);
    }

    animationClock.restart();
}

void Shop::draw(sf::RenderWindow &window) {
    for (const auto &item : shopItems) {
        window.draw(item);
    }
    for (int i = 0; i < 4; i++) {
        ballsprite[i].setTexture(ballTextures[i]);
        ballsprite[i].setPosition(sf::Vector2f(1000.f, (972.f / (ballTextures.size() + 1) * (i + 1)) - 25.f));
        float originalWidth = ballTextures[i].getSize().x;
        float originalHeight = ballTextures[i].getSize().y;
        ballsprite[i].setScale(80.f / originalWidth, 80.f / originalHeight);
        window.draw(ballsprite[i]);
    }
    int coins = readCoins();
    sf::Text CoinText;
    CoinText.setFont(font);
    CoinText.setCharacterSize(80);
    CoinText.setFillColor(sf::Color::Green);
    CoinText.setString("Coins: " + std::to_string(coins));
    CoinText.setPosition(610, 10);
    window.draw(CoinText);

    // Rysowanie animacji sprite
    updateAnimation();
    animatedSprite.setScale(0.15,0.15);
    window.draw(animatedSprite);
}

void Shop::updateAnimation() {
    sf::Time elapsed = animationClock.getElapsedTime();
    if (elapsed.asSeconds() > 0.2f) { // zmiana klatki co 0.1s
        animationFrame = (animationFrame + 1) % animatedTextures.size();
        animatedSprite.setTexture(animatedTextures[animationFrame]);
        animationClock.restart();
    }
}

// obsługa poruszania się po sklepie
void Shop::moveUp() {
    int coins = readCoins();
    if (selectedItemIndex - 1 >= 0) {
        if (coins >= ballPrices[selectedItemIndex])
            shopItems[selectedItemIndex].setFillColor(sf::Color::Green);
        else
            shopItems[selectedItemIndex].setFillColor(sf::Color::Red);
        selectedItemIndex--;
        shopItems[selectedItemIndex].setFillColor(sf::Color::White);
    }
}

// obsługa poruszania się po sklepie
void Shop::moveDown() {
    int coins = readCoins();
    if (selectedItemIndex + 1 < int(shopItems.size())) {
        if (coins >= ballPrices[selectedItemIndex])
            shopItems[selectedItemIndex].setFillColor(sf::Color::Green);
        else
            shopItems[selectedItemIndex].setFillColor(sf::Color::Red);
        selectedItemIndex++;
        shopItems[selectedItemIndex].setFillColor(sf::Color::White);
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
        return true;
    } else {
        sf::RenderWindow coinsWindow(sf::VideoMode(700, 500), "Settings");
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error: Could not load font arial.ttf" << std::endl;
        }
        coinsText.setFont(font);
        coinsText.setPosition(50, 230);
        coinsText.setString("!NIE MASZ WYSTARCZAJACO PIENIEDZY!");

        bool inCoinstext = true;
        while (inCoinstext) {
            sf::Event event;
            while (coinsWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    inCoinstext = false;
                } else if (event.type == sf::Event::KeyPressed) {
                    inCoinstext = false;
                }
            }
            coinsWindow.clear();
            coinsWindow.draw(coinsText);
            coinsWindow.display();
        }

        return false;
    }
}
