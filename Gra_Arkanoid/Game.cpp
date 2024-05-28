#include "Game.h"
#include "Object.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() : mWindow(sf::VideoMode(1728,972), "Super Galaxy Arkanoid")
{

}

Game::~Game() {}

void Game::run() {
    sf::Clock clock;
    //ładowanie tekstury tła
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        // Obsługa błędu ładowania pliku
        std::cerr << "Error: Could not load background.png" << std::endl;
        return;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(
        mWindow.getSize().x / static_cast<float>(backgroundTexture.getSize().x),
        mWindow.getSize().y / static_cast<float>(backgroundTexture.getSize().y)
        );

    while (mWindow.isOpen()) {
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mWindow.close();
        }

        mWindow.clear();
        mWindow.draw(background);
        mWindow.display();
    }
}
