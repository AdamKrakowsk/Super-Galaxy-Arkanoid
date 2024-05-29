#include "Game.h"
#include "Object.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game()
    : mWindow(sf::VideoMode(1728, 972), "Super Galaxy Arkanoid"),
    m_paddle(m_paddleTexture),
    m_PaddleSpeed(800.0f),
    m_BallSpeed(40000.0f),
    m_ball(m_ballTexture),
    m_ballVelocity(-m_BallSpeed, -m_BallSpeed){
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
    // Ładowanie tekstury pilki
    if (!m_ballTexture.loadFromFile("pilka.png")) {
        std::cerr << "Error: Could not load pilka.png" << std::endl;
        return;
    }
    // Ładowanie tekstury bloku
    if (!m_blockTexture.loadFromFile("blok.png")) {
        std::cerr << "Error: Could not load blok.png" << std::endl;
        return;
    }

    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(
        mWindow.getSize().x / static_cast<float>(m_backgroundTexture.getSize().x),
        mWindow.getSize().y / static_cast<float>(m_backgroundTexture.getSize().y)
        );

    // Tworzenie paletki
    createPaddle();
    // Tworzenie piłki
    createBall();
    // Tworzenie bloków
    createBlocks();

    while (mWindow.isOpen()) {
        sf::Event event;
        mWindow.setFramerateLimit(120);
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

        // sprawdzanie granic okna dla paletki
        if (newPosition.x < 0) {
            newPosition.x = 0;
        }
        if (newPosition.x + m_paddleSprite.getGlobalBounds().width > mWindow.getSize().x) {
            newPosition.x = mWindow.getSize().x - m_paddleSprite.getGlobalBounds().width;
        }

        m_paddleSprite.setPosition(newPosition);
        // Ruch piłki
        m_ballSprite.move(m_ballVelocity * deltaTime.asSeconds()*100.0f);

        // sprawdzanie granic okna dla pilki
        sf::Vector2f ballPosition = m_ballSprite.getPosition();
        if (ballPosition.x < 10 || ballPosition.x + m_ballSprite.getGlobalBounds().width+10 > mWindow.getSize().x) {
            m_ballVelocity.x = -m_ballVelocity.x;
        }
        if (ballPosition.y < 10) {
            m_ballVelocity.y = -m_ballVelocity.y;
        }

        // Check collision with paddle
        if (m_ballSprite.getGlobalBounds().intersects(m_paddleSprite.getGlobalBounds())) {
            m_ballVelocity.y = -m_ballVelocity.y;
            // Optionally adjust x velocity based on where the ball hit the paddle
        }

        // Check if ball is below the paddle (lose condition)
        if (ballPosition.y > mWindow.getSize().y) {
            // Reset ball position and velocity (you can customize this as needed)
            m_ballSprite.setPosition(864, 600);
            m_ballVelocity = sf::Vector2f(-m_BallSpeed, -m_BallSpeed);
        }
        render();
    }
}
//renderowanie okna
void Game::render() {
    mWindow.clear();
    mWindow.draw(m_backgroundSprite);
    mWindow.draw(m_paddleSprite);
    mWindow.draw(m_ballSprite);
    for (const auto& obj : m_objects) {
        mWindow.draw(*obj);
    }
    mWindow.display();
}

//tworzenie paletki
void Game::createPaddle() {
    m_paddleSprite.setTexture(m_paddleTexture);
    m_paddleSprite.setPosition(864, 900);
    float originalWidth = m_paddleTexture.getSize().x;
    float originalHeight = m_paddleTexture.getSize().y;

    // wymiary paletki
    float desiredWidth = 200.f;
    float desiredHeight = 50.f;


    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;

    // skalowanie paletki
    m_paddleSprite.setScale(scaleX, scaleY);
}

void Game::createBall() {
    m_ballSprite.setTexture(m_ballTexture);
    m_ballSprite.setPosition(864, 600);
    float originalWidth = m_ballTexture.getSize().x;
    float originalHeight = m_ballTexture.getSize().y;

    // pilki
    float desiredWidth = 20.f;
    float desiredHeight = 20.f;


    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;

    // skalowanie pilki
    m_ballSprite.setScale(scaleX, scaleY);

}


void Game::createBlocks() {
    // Tworzenie przykładowych bloków
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            sf::Color color = (j % 2 == 0) ? sf::Color::Red : sf::Color::Green;
            int hp = (j % 2 == 0) ? 2 : 1;
            Block block(80.f, 30.f, color, hp);
            block.setPosition(200.f + i * 100.f, 50.f + j * 50.f);
            m_objects.push_back(std::make_unique<Block>(block));
        }
    }
}
