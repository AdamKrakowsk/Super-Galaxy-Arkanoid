#include "Menu.h"

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
    }

    // Initialize menu items
    sf::Text playText, highscoresText, settingsText, shopText, exitText;

    playText.setFont(font);
    playText.setFillColor(sf::Color::Red);
    playText.setString("Play");
    playText.setPosition(sf::Vector2f(width / 2.f, height / (6.f + 1) * 1.f));

    highscoresText.setFont(font);
    highscoresText.setFillColor(sf::Color::White);
    highscoresText.setString("Highscores");
    highscoresText.setPosition(sf::Vector2f(width / 2.f, height / (6.f + 1) * 2.f));

    settingsText.setFont(font);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setString("Settings");
    settingsText.setPosition(sf::Vector2f(width / 2.f, height / (6.f + 1) * 3.f));

    shopText.setFont(font);
    shopText.setFillColor(sf::Color::White);
    shopText.setString("Shop");
    shopText.setPosition(sf::Vector2f(width / 2.f, height / (6.f + 1) * 4.f));

    exitText.setFont(font);
    exitText.setFillColor(sf::Color::White);
    exitText.setString("Exit");
    exitText.setPosition(sf::Vector2f(width / 2.f, height / (6.f + 1) * 5.f));

    menuItems.push_back(playText);
    menuItems.push_back(highscoresText);
    menuItems.push_back(settingsText);
    menuItems.push_back(shopText);
    menuItems.push_back(exitText);

    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow &window) {
    for (const auto &item : menuItems) {
        window.draw(item);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
