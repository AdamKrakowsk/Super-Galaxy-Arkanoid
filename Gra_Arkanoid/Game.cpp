#include "Game.h"
#include "Block.h"
#include "Bonus.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

const sf::Time TimePerFrame = sf::seconds(1.f / 240.f);

Game::Game()
    : mWindow(sf::VideoMode(1728, 972), "Super Galaxy Arkanoid"),
    m_paddle(m_paddleTexture),
    m_ball(m_ballTexture),
    m_PaddleSpeed(1000.0f),
    m_BallSpeed(1000.0f),
    m_ballVelocity(-m_BallSpeed, -m_BallSpeed),
    m_highscore(),
    m_gameOver(false){
}

Game::~Game() {}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
     m_gameClock.restart();


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

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font arial.ttf" << std::endl;
    }



    m_currentTimeText.setFont(m_font);
    m_currentTimeText.setCharacterSize(50);
    m_currentTimeText.setFillColor(sf::Color::White);
    m_currentTimeText.setPosition(mWindow.getSize().x / 2.f - 100.f, 10.f);

    m_highscoreText.setFont(m_font);
    m_highscoreText.setCharacterSize(50);
    m_highscoreText.setFillColor(sf::Color::White);
    m_highscoreText.setPosition(10.f, 10.f);


    sm.Soundtrack_play();

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

            if (m_gameClock.getElapsedTime().asSeconds() > m_highscore.getHighscore()) {
                // Jeśli czas trwania gry jest krótszy niż highscore, zaktualizuj highscore
                m_highscore.setHighscore(static_cast<int>(m_gameClock.getElapsedTime().asSeconds()));
            }

            for (auto it = m_objects.begin(); it != m_objects.end(); ) {
                m_ball.handleCollision(**it);

                // Usuwanie zniszczonych bloków
                if ((*it)->isDestroyed()) {
                    it = m_objects.erase(it);
                } else {
                    ++it;
                }
            }


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

void Game::restartGame() {
    m_gameOver = false;
    m_isBallAttached = true;
    m_ballSprite.setPosition(864, 600);
    m_ballVelocity = sf::Vector2f(-m_BallSpeed, -m_BallSpeed);
    m_paddleSprite.setPosition(864, 900);
    createBlocks();
    m_gameClock.restart();
}




void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (m_gameOver && key == sf::Keyboard::R && isPressed) {
        restartGame();
    }
    if (key == sf::Keyboard::A || key == sf::Keyboard::Left) {
        m_isMovingLeft = isPressed;
    }
    else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) {
        m_isMovingRight = isPressed;
    }
    else if (key == sf::Keyboard::Space && isPressed && m_isBallAttached) {
        m_isBallAttached = false;
        m_ballVelocity = sf::Vector2f(-m_BallSpeed, -m_BallSpeed);  // Wystrzelenie piłki
    }
}

void Game::update(sf::Time deltaTime) {
    if (m_gameOver) return;


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

    if (m_isBallAttached) {
        // Aktualizacja pozycji piłki, gdy jest przyklejona do paletki
        m_ballSprite.setPosition(
            m_paddleSprite.getPosition().x + m_paddleSprite.getGlobalBounds().width / 2.f - m_ballSprite.getGlobalBounds().width / 2.f,
            m_paddleSprite.getPosition().y - m_ballSprite.getGlobalBounds().height
            );
    } else {
        // aktualizacja ruchu pilki
        m_ballSprite.move(m_ballVelocity * deltaTime.asSeconds());
        sf::Vector2f ballPosition = m_ballSprite.getPosition();

        // sprawdzanie granic dla pilki
        if (ballPosition.x < 0 || ballPosition.x + m_ballSprite.getGlobalBounds().width > mWindow.getSize().x) {
            m_ballVelocity.x = -m_ballVelocity.x;

        }
        if (ballPosition.y < 0) {
            m_ballVelocity.y = -m_ballVelocity.y;
            sm.collision_sound();
        }

        // sprawdzanie kolizji z paletka
        if (m_ballSprite.getGlobalBounds().intersects(m_paddleSprite.getGlobalBounds())) {
            float paddleCenterX = m_paddleSprite.getPosition().x + m_paddleSprite.getGlobalBounds().width / 2.f;
            float ballCenterX = m_ballSprite.getPosition().x + m_ballSprite.getGlobalBounds().width / 2.f;

            float distanceFromCenter = ballCenterX - paddleCenterX;
            float maxBounceAngle = 75.f * (3.14159f / 180.f);  // maksymalny kąt odbicia (75 stopni w radianach)
            float normalizedDistance = distanceFromCenter / (m_paddleSprite.getGlobalBounds().width / 2.f);

            float bounceAngle = normalizedDistance * maxBounceAngle;
            float speed = sqrt(m_ballVelocity.x * m_ballVelocity.x + m_ballVelocity.y * m_ballVelocity.y);
            m_ballVelocity.x = speed * sin(bounceAngle);
            m_ballVelocity.y = -speed * cos(bounceAngle);
            sm.collision_sound();
        }

        // resetowanie pilki jak dotknie dolu okna
        if (ballPosition.y > mWindow.getSize().y) {
            m_ballSprite.setPosition(864, 600);
            m_ballVelocity = sf::Vector2f(-m_BallSpeed, -m_BallSpeed);
            m_isBallAttached = true;  // Przyklejenie piłki po jej zresetowaniu
        }

        // sprawdzanie kolizji z blokami
        for (auto& object : m_objects) {
            if (m_ballSprite.getGlobalBounds().intersects(object->getBounds())) {
                m_ballVelocity.y = -m_ballVelocity.y;
                object->takeDamage();
                if (object->isDestroyed()) {
                    createBonus(object->getBounds().left, object->getBounds().top);
                }
            }
        }

    // Zaktualizuj teksty z aktualnym czasem i highscore
    m_currentTimeText.setString("Time: " + std::to_string(static_cast<int>(m_gameClock.getElapsedTime().asSeconds())));
    m_highscoreText.setString("Highscore: " + std::to_string(m_highscore.getHighscore()));

    if (m_objects.empty()) {
        m_gameOver = true;
        int finalTime = static_cast<int>(m_gameClock.getElapsedTime().asSeconds());
        if (finalTime < m_highscore.getHighscore() || m_highscore.getHighscore() == 0) {
            m_highscore.setHighscore(finalTime);
            m_highscore.saveHighscore();
        }
    }

}
    for (auto& bonus : m_bonuses) {
        bonus.update(deltaTime);
        if (bonus.getBounds().intersects(m_paddleSprite.getGlobalBounds()) && !bonus.isCaught()) {
            bonus.catchBonus();
            m_BallSpeed *= 1.15f; // Increase ball speed by 15%
            m_ballVelocity.x *= 1.15f;
            m_ballVelocity.y *= 1.15f;
        }
    }

    m_bonuses.erase(std::remove_if(m_bonuses.begin(), m_bonuses.end(), [](const Bonus& bonus) {
                        return bonus.isCaught() || bonus.getBounds().top > 972; // Remove caught bonuses or those out of the window
                    }), m_bonuses.end());
}


void Game::render() {
    mWindow.clear();
    mWindow.draw(m_backgroundSprite);
    mWindow.draw(m_paddleSprite);
    mWindow.draw(m_ballSprite);
    for (const auto& obj : m_objects) {
        mWindow.draw(*obj);
    }
    for (auto& bonus : m_bonuses) {
        bonus.render(mWindow);
    }

    mWindow.draw(m_currentTimeText); // Wyświetlanie aktualnego czasu
    mWindow.draw(m_highscoreText); // Wyświetlanie highscore
    m_highscore.draw(mWindow);

    if (m_gameOver) {
        sf::Text gameOverText;
        gameOverText.setFont(m_font);
        gameOverText.setString("Game Over! Press R to Restart");
        gameOverText.setCharacterSize(30);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setPosition(
            mWindow.getSize().x / 2.f - gameOverText.getLocalBounds().width / 2.f,
            mWindow.getSize().y / 2.f - gameOverText.getLocalBounds().height / 2.f
            );
        mWindow.draw(gameOverText);

    }

    mWindow.display();
}
void Game::createBonus(float x, float y) {
    Bonus bonus;
    bonus.createBonus();
    bonus.setPosition(x, y);
    m_bonuses.push_back(bonus);
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
    int rows = 1;
    int columns = 5; //17
    float blockWidth = 80.f;
    float blockHeight = 30.f;
    float startX = 30.f;        // miejsca początkowe 30
    float startY = 100.f;
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


