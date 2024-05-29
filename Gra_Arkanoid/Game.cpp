#include "Game.h"
#include "Object.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

Game::Game()
    : mWindow(sf::VideoMode(1728, 972), "Super Galaxy Arkanoid"),
    m_paddle(m_paddleTexture),
    m_PaddleSpeed(800.0f) {
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            m_PaddleVelocity.x -= m_PaddleSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            m_PaddleVelocity.x += m_PaddleSpeed;
        }
        m_paddleSprite.move(m_PaddleVelocity * clock.restart().asSeconds());
        sf::Time deltaTime = clock.restart();
        sf::Vector2f newPosition = m_paddleSprite.getPosition() + m_PaddleVelocity * deltaTime.asSeconds();

        // Check boundaries
        if (newPosition.x < 0) {
            newPosition.x = 0;
        }
        if (newPosition.x + m_paddleSprite.getGlobalBounds().width > mWindow.getSize().x) {
            newPosition.x = mWindow.getSize().x - m_paddleSprite.getGlobalBounds().width;
        }

        m_paddleSprite.setPosition(newPosition);
        render();
    }
}
//renderowanie okna
void Game::render() {
    mWindow.clear();
    mWindow.draw(m_backgroundSprite);
    mWindow.draw(m_paddleSprite);
    for (const auto& obj : m_objects) {
        mWindow.draw(*obj);
    }
    mWindow.display();
}

//tworzenie paletki
void Game::createPaddle() {
    m_paddleSprite.setTexture(m_paddleTexture);
    m_paddleSprite.setPosition(864, 870);
    float originalWidth = m_paddleTexture.getSize().x;
    float originalHeight = m_paddleTexture.getSize().y;

    // wymiary paletki
    float desiredWidth = 200.f;
    float desiredHeight = 30.f;


    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;

    // skalowanie paletki
    m_paddleSprite.setScale(scaleX, scaleY);
}
