#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>
// Funkcje które pozwalają zarządzać daną klasą


Menu::Menu(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font arial.ttf" << std::endl;
    }

    // Inicjalizacja przedmiotów w menu
    sf::Text playText, highscoreText, settingsText, shopText, exitText;

    playText.setFont(font);
    playText.setFillColor(sf::Color::Red);
    playText.setString("Play");
    playText.setPosition(sf::Vector2f(width / 5.f, height / (6.f + 1) * 1.f));
    playText.setCharacterSize(72); // Ustawienie rozmiaru tekstu

    highscoreText.setFont(font);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setString("Highscore");
    highscoreText.setPosition(sf::Vector2f(width / 5.f, height / (6.f + 1) * 2.f));
    highscoreText.setCharacterSize(72);

    settingsText.setFont(font);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setString("Settings");
    settingsText.setPosition(sf::Vector2f(width / 5.f, height / (6.f + 1) * 3.f));
    settingsText.setCharacterSize(72);

    shopText.setFont(font);
    shopText.setFillColor(sf::Color::White);
    shopText.setString("Shop");
    shopText.setPosition(sf::Vector2f(width / 5.f, height / (6.f + 1) * 4.f));
    shopText.setCharacterSize(72);

    exitText.setFont(font);
    exitText.setFillColor(sf::Color::White);
    exitText.setString("Exit");
    exitText.setPosition(sf::Vector2f(width / 5.f, height / (6.f + 1) * 5.f));
    exitText.setCharacterSize(72);


    menuItems.push_back(playText);
    menuItems.push_back(highscoreText);
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

// funkcja do poruszania w menu
void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}


// funkcja do poruszania w menu
void Menu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}




// funkcja do korzystania z opcji w menu
void Menu::showSettings(std::function<void(int, int)> setVolumes) {
    sf::RenderWindow settingsWindow(sf::VideoMode(700, 500), "Settings");

    sf::Text soundtrackVolumeText, collisionVolumeText, settingsText, settingsText1;

    settingsText.setFont(font);
    settingsText.setFillColor(sf::Color::Green);
    settingsText.setString("OPCJE");
    settingsText.setPosition(20.f, 20.f);


    settingsText1.setFont(font);
    settingsText1.setFillColor(sf::Color::Green);
    settingsText1.setString("(strzalkami sie ustawia, esc zapisuje)");
    settingsText1.setPosition(20.f, 400.f);

    soundtrackVolumeText.setFont(font);
    soundtrackVolumeText.setFillColor(sf::Color::White);
    soundtrackVolumeText.setString("Soundtrack Volume: 5");
    soundtrackVolumeText.setPosition(120.f, 120.f);

    collisionVolumeText.setFont(font);
    collisionVolumeText.setFillColor(sf::Color::White);
    collisionVolumeText.setString("Collision Volume: 5");
    collisionVolumeText.setPosition(120.f, 240.f);

    int soundtrackVolume = 5;
    int collisionVolume = 5;

    bool inSettings = true;
    while (inSettings) {
        sf::Event event;
        while (settingsWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                inSettings = false;
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    inSettings = false;
                } else if (event.key.code == sf::Keyboard::Left) {
                    if (soundtrackVolume > 0) {
                        soundtrackVolume -= 1;
                        setVolumes(soundtrackVolume, collisionVolume);
                        soundtrackVolumeText.setString("Soundtrack Volume: " + std::to_string(soundtrackVolume));
                    }
                } else if (event.key.code == sf::Keyboard::Right) {
                    if (soundtrackVolume < 100) {
                        soundtrackVolume += 1;
                        setVolumes(soundtrackVolume, collisionVolume);
                        soundtrackVolumeText.setString("Soundtrack Volume: " + std::to_string(soundtrackVolume));
                    }
                } else if (event.key.code == sf::Keyboard::Down) {
                    if (collisionVolume > 0) {
                        collisionVolume -= 1;
                        setVolumes(soundtrackVolume, collisionVolume);
                        collisionVolumeText.setString("Collision Volume: " + std::to_string(collisionVolume));
                    }
                } else if (event.key.code == sf::Keyboard::Up) {
                    if (collisionVolume < 100) {
                        collisionVolume += 1;
                        setVolumes(soundtrackVolume, collisionVolume);
                        collisionVolumeText.setString("Collision Volume: " + std::to_string(collisionVolume));
                    }
                }
            }
        }

        settingsWindow.clear();
        settingsWindow.draw(settingsText);
        settingsWindow.draw(soundtrackVolumeText);
        settingsWindow.draw(collisionVolumeText);
        settingsWindow.draw(settingsText1);
        settingsWindow.display();
    }
}




// Funkcja pokazująca w menu HighScore
void Menu::showHighscore() {

        std::ifstream file("highscore.txt");
        if (file.is_open()) {
            file >> highscore;
            file.close();
        } else {
            std::cerr << "Error: Could not open highscore.txt for reading" << std::endl;
        }

    sf::Text highscoreText;
    sf::RenderWindow HighscoreWindow(sf::VideoMode(400, 250), "Highscore");
    highscoreText.setFont(font);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setString("Highscore: " + std::to_string(highscore));
    highscoreText.setPosition(120.f, 100.f);

    bool inHighscore = true;
    while (inHighscore) {
        sf::Event event;
        while (HighscoreWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                inHighscore = false;
            }
         else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                inHighscore = false;
            }
        }
        }
    HighscoreWindow.clear();
    HighscoreWindow.draw(highscoreText);
    HighscoreWindow.display();
    }

}
