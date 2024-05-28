#include "Game.h"
#include "Object.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

Game::Game()
    : mWindow(sf::VideoMode(1728, 972), "Super Galaxy Arkanoid"),
    m_PaddleSpeed(200.0f) {
}

Game::~Game() {}

void Game::run() {
    sf::Clock clock;
    // Ładowanie tekstury tła
    if (!m_backgroundTexture.loadFromFile("background.png")) {
        std::cerr << "Error: Could not load background.png" << std::endl;
        return;
    }
    // Ładowanie tekstury paletki
    if (!m_paddleTexture.loadFromFile("paletka.png")) {
        std::cerr << "Error: Could not load paletka.png" << std::endl;
        return;
    }

    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(
        mWindow.getSize().x / static_cast<float>(m_backgroundTexture.getSize().x),
        mWindow.getSize().y / static_cast<float>(m_backgroundTexture.getSize().y)
        );

    // Tworzenie paletki
    createPaddle();

    while (mWindow.isOpen()) {
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mWindow.close();
        }

        // Ruch paletki
        m_PaddleVelocity = sf::Vector2f(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            m_PaddleVelocity.x -= m_PaddleSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            m_PaddleVelocity.x += m_PaddleSpeed;
        }
        m_paddleSprite.move(m_PaddleVelocity * clock.restart().asSeconds());

        render();
    }
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(m_backgroundSprite);
    mWindow.draw(m_paddleSprite);
    for (const auto& obj : m_objects) {
        mWindow.draw(*obj);
    }
    mWindow.display();
}

void Game::createPaddle() {
    m_paddleSprite.setTexture(m_paddleTexture);
    m_paddleSprite.setPosition(50, 800);

    // while (checkCollisionWithWalls(m_paddleSprite.getGlobalBounds())) {
    //     m_paddleSprite.move(10, 0);
    // }
}
