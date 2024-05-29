#include "Game.h"
#include "Object.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

const sf::Time TimePerFrame = sf::seconds(1.f / 240.f);

Game::Game()
    : mWindow(sf::VideoMode(1728, 972), "Super Galaxy Arkanoid"),
    m_paddle(m_paddleTexture),
    m_ball(m_ballTexture),
    m_PaddleSpeed(800.0f),
    m_BallSpeed(500.0f),
    m_ballVelocity(-m_BallSpeed, -m_BallSpeed) {
}

Game::~Game() {}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // Load textures
    if (!m_backgroundTexture.loadFromFile("background.png")) {
        std::cerr << "Error: Could not load background.png" << std::endl;
        return;
    }
    if (!m_paddleTexture.loadFromFile("paletka.png")) {
        std::cerr << "Error: Could not load paletka.png" << std::endl;
        return;
    }
    if (!m_ballTexture.loadFromFile("pilka.png")) {
        std::cerr << "Error: Could not load pilka.png" << std::endl;
        return;
    }
    if (!m_blockTexture.loadFromFile("blok.png")) {
        std::cerr << "Error: Could not load blok.png" << std::endl;
        return;
    }

    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(
        mWindow.getSize().x / static_cast<float>(m_backgroundTexture.getSize().x),
        mWindow.getSize().y / static_cast<float>(m_backgroundTexture.getSize().y)
        );

    createPaddle();
    createBall();
    createBlocks();

    while (mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();
        if (event.type == sf::Event::KeyPressed)
            handlePlayerInput(event.key.code, true);
        if (event.type == sf::Event::KeyReleased)
            handlePlayerInput(event.key.code, false);
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::A || key == sf::Keyboard::Left) {
        m_isMovingLeft = isPressed;
    }
    else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) {
        m_isMovingRight = isPressed;
    }
}

void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (m_isMovingLeft)
        movement.x -= m_PaddleSpeed;
    if (m_isMovingRight)
        movement.x += m_PaddleSpeed;

    m_paddleSprite.move(movement * deltaTime.asSeconds());
    sf::Vector2f newPosition = m_paddleSprite.getPosition();

    // sprawdzanie granic dla paletki
    if (newPosition.x < 0) {
        newPosition.x = 0;
    }
    if (newPosition.x + m_paddleSprite.getGlobalBounds().width > mWindow.getSize().x) {
        newPosition.x = mWindow.getSize().x - m_paddleSprite.getGlobalBounds().width;
    }
    m_paddleSprite.setPosition(newPosition);

    // aktualizacja ruchu pilki
    m_ballSprite.move(m_ballVelocity * deltaTime.asSeconds());
    sf::Vector2f ballPosition = m_ballSprite.getPosition();

    // sprawdzanie granic dla pilki
    if (ballPosition.x < 0 || ballPosition.x + m_ballSprite.getGlobalBounds().width > mWindow.getSize().x) {
        m_ballVelocity.x = -m_ballVelocity.x;
    }
    if (ballPosition.y < 0) {
        m_ballVelocity.y = -m_ballVelocity.y;
    }

    // sprawdzanie kolizji z paletka
    if (m_ballSprite.getGlobalBounds().intersects(m_paddleSprite.getGlobalBounds())) {
        m_ballVelocity.y = -m_ballVelocity.y;
        // Optionally adjust x velocity based on where the ball hit the paddle
    }

    // resetowanie pilki jak dotknie dolu okna
    if (ballPosition.y > mWindow.getSize().y) {
        m_ballSprite.setPosition(864, 600);
        m_ballVelocity = sf::Vector2f(-m_BallSpeed, -m_BallSpeed);
    }
}

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

void Game::createPaddle() {
    m_paddleSprite.setTexture(m_paddleTexture);
    m_paddleSprite.setPosition(864, 900);
    float originalWidth = m_paddleTexture.getSize().x;
    float originalHeight = m_paddleTexture.getSize().y;

    float desiredWidth = 200.f;
    float desiredHeight = 50.f;

    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;

    m_paddleSprite.setScale(scaleX, scaleY);
}

void Game::createBall() {
    m_ballSprite.setTexture(m_ballTexture);
    m_ballSprite.setPosition(864, 600);
    float originalWidth = m_ballTexture.getSize().x;
    float originalHeight = m_ballTexture.getSize().y;

    float desiredWidth = 20.f;
    float desiredHeight = 20.f;

    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;

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


