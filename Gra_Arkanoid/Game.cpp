#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <random>

Game::Game()
    : mWindow(sf::VideoMode(1728, 972), "Super Galaxy Arkanoid"),
    m_paddle(m_paddleTexture),
    m_ball(m_ballTexture),
    m_PaddleSpeed(800.0f),
    m_BallSpeed(40000.0f),
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
    // // Ładowanie tekstury bloku
    // if (!m_blockTexture.loadFromFile("blok.png")) {
    //     std::cerr << "Error: Could not load blok.png" << std::endl;
    //     return;
    // }

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

    // Tworzenie przykładowych bloków i wierszy i kolumn
    int rows = 6;
    int columns = 17;
    float blockWidth = 80.f;
    float blockHeight = 30.f;
    float startX = 30.f;        // miejsca początkowe
    float startY = 50.f;
    float horizontalSpacing = 20.f; // Odstęp w poziomie
    float verticalSpacing = 20.f; // Odstęp w pionie
    srand(time(0));         // dodanie losowości
    int tab[columns][rows];
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            tab[i][j]=rand()%3;
        }
    }

        // Pętla pozwalająca na ustawienie kolumn, wierszy, kolorów, hp
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            sf::Color color;
            int hp = 0;

            if (tab[i][j] == 0) {
                color = sf::Color::Red;
                hp = 3;
            } else if (tab[i][j] == 1) {
                color = sf::Color::Green;
                hp = 2;
            } else if (tab[i][j] == 2) {
                color = sf::Color::Blue;
                hp = 1;
            }
            Block block(blockWidth, blockHeight, color, hp);
            block.setPosition(startX + i * (blockWidth + horizontalSpacing), startY + j * (blockHeight + verticalSpacing));
            m_objects.push_back(std::make_unique<Block>(block));
        }
    }
}


