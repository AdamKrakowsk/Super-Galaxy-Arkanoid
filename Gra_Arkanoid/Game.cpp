#include "Game.h"
#include "Block.h"
#include "Bonus.h"
#include "HeartSystem.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <fstream>
// Funkcje które pozwalają zarządzać daną klasą

const sf::Time TimePerFrame = sf::seconds(1.f / 240.f);

// Inicjalizacja obiektów
Game::Game()
    : mWindow(sf::VideoMode(1728, 972), "Super Galaxy Arkanoid"),
    m_paddle(m_paddleTexture),
    m_ball(m_ballTexture),
    m_heartSystem(3, m_heartTexture, 100.f, 100.f),
    m_PaddleSpeed(900.0f),
    m_BallSpeed(800.0f),
    m_lives(3),
    m_ballVelocity(-m_BallSpeed, -m_BallSpeed),
    m_highscore(),
    m_gameOver(false),
    coins(0),
    m_menu(mWindow.getSize().x, mWindow.getSize().y),
    m_shop(mWindow.getSize().x, mWindow.getSize().y),
    m_isInMenu(true),
    m_isInShop(false) {
    loadCoinsFromFile("coins.txt");
    sm.setCollisionVolume(5);
    sm.setSoundtrackVolume(2);
    if (!m_heartTexture.loadFromFile("life.png")) {
        std::cerr << "Error: Could not load life.png" << std::endl;
        return;
    }
    if (m_heartTexture.getSize().x == 0 || m_heartTexture.getSize().y == 0) {
        std::cerr << "Error: Failed to load heart.png texture" << std::endl;
        // Możesz tutaj zakończyć program lub podjąć odpowiednie działania
    }
}
//destruktor zapisujący ilość
Game::~Game() { saveCoinsToFile("coins.txt");}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    m_gameClock.restart();


    //wczytywanie tekstur
    if (!m_backgroundTexture.loadFromFile("background.png")) {
        std::cerr << "Error: Could not load background.png" << std::endl;
        return;
    }
    if (!m_paddleTexture.loadFromFile("paletka.png")) {
        std::cerr << "Error: Could not load paletka.png" << std::endl;
        return;
    }
    if (!m_ballTexture.loadFromFile("ball1.png")) {
        std::cerr << "Error: Could not load pilka.png" << std::endl;
        return;
    }

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font arial.ttf" << std::endl;
    }


    // wielkość liter i napisy w grze
    m_currentTimeText.setFont(m_font);
    m_currentTimeText.setCharacterSize(50);
    m_currentTimeText.setFillColor(sf::Color::White);
    m_currentTimeText.setPosition(mWindow.getSize().x / 2.f - 300.f, 10.f);

    m_highscoreText.setFont(m_font);
    m_highscoreText.setCharacterSize(50);
    m_highscoreText.setFillColor(sf::Color::White);
    m_highscoreText.setPosition(10.f, 10.f);

    m_coinsText.setFont(m_font);
    m_coinsText.setCharacterSize(50);
    m_coinsText.setFillColor(sf::Color::White);
    m_coinsText.setPosition(mWindow.getSize().x - 650, 10);

    sm.Soundtrack_play();
    // ustawianie tła
    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(
        mWindow.getSize().x / static_cast<float>(m_backgroundTexture.getSize().x),
        mWindow.getSize().y / static_cast<float>(m_backgroundTexture.getSize().y)
        );

    // tworzenie obiektów
    createPaddle();
    createBall();
    createBlocks();


    // Kiedy okno jest otwarte i procesy w nim zawarte
    while (mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            if (!m_isInMenu && !m_isInShop) {
                update(TimePerFrame);
            }

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

// restartowanie gry
void Game::restartGame() {
    m_objects.clear();
    createPaddle();
    createBall();
    createBlocks();
    m_gameClock.restart();
    m_gameOver = false;
    m_showGameOverScreen = true;
    m_isMovingLeft = false;  // Zresetuj zmienne odpowiadające za ruch paletki
    m_isMovingRight = false;
    m_lives=3;
    m_isBallAttached = true;
}

// korzystanie z przycisków przez użytkowanika
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if(m_showGameOverScreen && isPressed && key== sf::Keyboard::Space){
        m_isInMenu = true;
        m_showGameOverScreen = false;
    }
    else if (m_isInMenu) {
        if (key == sf::Keyboard::Up && isPressed) {
            m_menu.moveUp();
        } else if (key == sf::Keyboard::Down && isPressed) {
            m_menu.moveDown();
        } else if (key == sf::Keyboard::Enter && isPressed) {
            int selectedItem = m_menu.getPressedItem();
            if (selectedItem == 0) { // Play
                m_isInMenu = false;
                startGame();
            } else if (selectedItem == 1) { // Highscores
                m_menu.showHighscore();
            } else if (selectedItem == 2) { // Settings
                showSettings();
            } else if (selectedItem == 3) { // Shop
                m_isInMenu = false;
                m_isInShop = true;
            } else if (selectedItem == 4) { // Exit
                mWindow.close();
            }
        }
    } else if (m_isInShop) {
        if (key == sf::Keyboard::Up && isPressed) {
            m_shop.moveUp();
        } else if (key == sf::Keyboard::Down && isPressed) {
            m_shop.moveDown();
        } else if (key == sf::Keyboard::Enter && isPressed) {
            saveCoinsToFile("coins.txt");
            m_shop.getSelectedItemIndex();
            m_shop.readCoins();
            m_shop.purchaseBall();
            if(m_shop.getSelectedTexture().getSize().x !=0 ||m_shop.getSelectedTexture().getSize().y!=0){
            m_ballSprite.setTexture(m_shop.getSelectedTexture());
            }
            else{
                m_ballSprite.setTexture(m_ballTexture);
            }
            loadCoinsFromFile("coins.txt");
            m_isInShop = false;
            m_isInMenu = true;
        } else if (key == sf::Keyboard::Escape && isPressed) {
            m_isInShop = false;
            m_isInMenu = true;
        }
    } else {
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
}




// obsługiwanie w czasie gry
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
            float maxBounceAngle = 45.f * (3.14159f / 180.f);  // maksymalny kąt odbicia (45 stopni w radianach)
            float normalizedDistance = distanceFromCenter / (m_paddleSprite.getGlobalBounds().width / 2.f);

            float bounceAngle = normalizedDistance * maxBounceAngle;
            float speed = sqrt(m_ballVelocity.x * m_ballVelocity.x + m_ballVelocity.y * m_ballVelocity.y);
            m_ballVelocity.x = speed * sin(bounceAngle);
            m_ballVelocity.y = -speed * cos(bounceAngle);
            sm.collision_sound();
        }

        // resetowanie pilki jak dotknie dolu okna i obsluga żyć
        if (ballPosition.y > mWindow.getSize().y) {
            m_heartSystem.loseHeart();
            m_lives--;
            if (m_lives > 0) {
                m_ballSprite.setPosition(864, 600);
                m_ballVelocity = sf::Vector2f(-m_BallSpeed, -m_BallSpeed);
                m_isBallAttached = true;
            } else {
                m_gameOver = true;
                restartGame();
            }
        }

        // sprawdzanie kolizji z blokami
        for (auto& object : m_objects) {
            if (m_ballSprite.getGlobalBounds().intersects(object->getBounds())) {
                m_ballVelocity.y = -m_ballVelocity.y;
                object->takeDamage();
                sm.collision_sound();
                if (object->isDestroyed()) {
                    bonuslos=rand()%30;
                    switch (bonuslos) {
                    case 0: {
                        if (!m_bonusTexture.loadFromFile("przyspieszeniepilki.png")) {
                            std::cerr << "Error loading bonus texture" << std::endl;
                        }
                        createBonus(object->getBounds().left, object->getBounds().top, bonuslos);
                        break;
                    }
                    case 1: {
                        if (!m_bonus1Texture.loadFromFile("powiekszeniepaletki.png")) {
                            std::cerr << "Error loading bonus texture" << std::endl;
                        }
                        createBonus(object->getBounds().left, object->getBounds().top, bonuslos);
                        break;
                    }
                    case 2: {
                        if (!m_bonus2Texture.loadFromFile("kasa.png")) {
                            std::cerr << "Error loading bonus texture" << std::endl;
                        }
                        createBonus(object->getBounds().left, object->getBounds().top, bonuslos);
                        break;
                    }
                    case 3: {
                        if (!m_bonus3Texture.loadFromFile("przyspieszeniepaletki.png")) {
                            std::cerr << "Error loading bonus texture" << std::endl;
                        }
                        createBonus(object->getBounds().left, object->getBounds().top, bonuslos);


                    }
                    default:{}

                    }

                }
                // Zwiększanie liczby coinsów za uderzenie w blok
                coins += 1;


            }
        }
    }
     // pętla z obsługą bonusów
    for (auto& bonus : m_bonuses) {
        bonus.update(deltaTime);
        if (bonus.getBounds().intersects(m_paddleSprite.getGlobalBounds()) && !bonus.isCaught()) {
            bonus.catchBonus();
            int bonusType = bonus.getType(); // Pobieramy typ bonusu, który został złapany
            switch(bonusType){
            case 0:
            {
                m_BallSpeed *= 1.1f;
                m_ballVelocity.x *= 1.1f;
                m_ballVelocity.y *= 1.1f;
                break;
            }
            case 1:
            {
                m_paddleSprite.setTexture(m_paddleTexture);
                float originalWidth = m_paddleTexture.getSize().x;
                float originalHeight = m_paddleTexture.getSize().y;
                lastW *= 1.15;
                float desiredWidth = lastW;
                float desiredHeight = lastH;

                float scaleX = desiredWidth / originalWidth;
                float scaleY = desiredHeight / originalHeight;

                m_paddleSprite.setScale(scaleX, scaleY);
                break;
            }

            case 2:{
                coins+=50;
                break;

            }
            case 3:{
                // Zwiększ prędkość paletki
                m_PaddleSpeed *= 1.2f;
                break;
            }

            }
        }
    }

    m_bonuses.erase(std::remove_if(m_bonuses.begin(), m_bonuses.end(), [](const Bonus& bonus) {
                        return bonus.isCaught() || bonus.getBounds().top > 972; // usuwanie bonusów, które zlapano albo wylecialy za okno
                    }), m_bonuses.end());

    // Zaktualizuj teksty z aktualnym czasem i highscore i coinsami
    m_currentTimeText.setString("Time: " + std::to_string(static_cast<int>(m_gameClock.getElapsedTime().asSeconds())));
    m_highscoreText.setString("Highscore: " + std::to_string(m_highscore.getHighscore()));
    m_coinsText.setString("Coins: " + std::to_string(coins));

    if (m_objects.empty()) {
        m_gameOver = true;
        int finalTime = static_cast<int>(m_gameClock.getElapsedTime().asSeconds());
        if (finalTime < m_highscore.getHighscore() || m_highscore.getHighscore() == 0) {
            m_highscore.setHighscore(finalTime);
            m_highscore.saveHighscore();
        }
    }

}

// rendereowanie obiektów
void Game::render() {
    mWindow.clear();
    if (m_showGameOverScreen) {
        mWindow.draw(m_backgroundSprite);
        sf::Text gameOverText;
        gameOverText.setFont(m_font);
        gameOverText.setString("GAME OVER! PRESS SPACED TO GO TO MENU");
        gameOverText.setCharacterSize(30);
        gameOverText.setFillColor(sf::Color::White);
        mWindow.clear();
        gameOverText.setPosition(
            mWindow.getSize().x / 2.f - gameOverText.getLocalBounds().width / 2.f,
            mWindow.getSize().y / 2.f - gameOverText.getLocalBounds().height / 2.f
            );
        mWindow.draw(gameOverText);


    } else if (m_isInMenu) {
        mWindow.draw(m_backgroundSprite);
        m_menu.draw(mWindow);
    } else if (m_isInShop) {
        mWindow.draw(m_backgroundSprite);
        m_shop.draw(mWindow);
    } else {
        mWindow.draw(m_backgroundSprite);
        mWindow.draw(m_paddleSprite);
        mWindow.draw(m_ballSprite);
        for (int i = 0; i < m_lives; ++i) {
            sf::Sprite heart;
            heart.setTexture(m_heartTexture);
            heart.setPosition(1630 - i * 80, 10);
            heart.setScale(0.2, 0.2);
            mWindow.draw(heart);
        }
        for (const auto& obj : m_objects) {
            mWindow.draw(*obj);
        }
        for (auto& bonus : m_bonuses) {
            bonus.render(mWindow);
        }
        mWindow.draw(m_currentTimeText); // Wyświetlanie aktualnego czasu
        mWindow.draw(m_highscoreText); // Wyświetlanie highscore
        mWindow.draw(m_coinsText); // Wyświetlanie liczby coinsów
        m_highscore.draw(mWindow);

        if (m_gameOver) {
            sf::Text gameOverText;
            gameOverText.setFont(m_font);
            m_BallSpeed = 800.0f;
            m_ballVelocity.x = 800.0f;
            m_ballVelocity.y = 800.0f;
            gameOverText.setString("YOU WIN! PRESS R TO GO TO MENU");
            gameOverText.setCharacterSize(30);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setPosition(
                mWindow.getSize().x / 2.f - gameOverText.getLocalBounds().width / 2.f,
                mWindow.getSize().y / 2.f - gameOverText.getLocalBounds().height / 2.f
                );
            mWindow.clear();
            mWindow.draw(gameOverText);

        }
    }
    mWindow.display();
}

// tworzenie bonusów
void Game::createBonus(float x, float y, int bonusType) {
    Bonus bonus;
    bonus.createBonus();
    switch (bonusType) {
    case 0: {
        bonus.setTexture(m_bonusTexture);
        bonus.setType(Bonus::SpeedUp); // Ustawienie typu bonusu na Przyspieszenie
        break;
    }
    case 1: {
        bonus.setTexture(m_bonus1Texture);
        bonus.setType(Bonus::PaddleEnlarge); // Ustawienie typu bonusu na PowiekszeniePaletki
        break;
    }
    case 2: {
        bonus.setTexture(m_bonus2Texture);
        bonus.setType(Bonus::ExtraCoins); // Ustawienie typu bonusu na DodatkoweMonety
        break;
    }
    case 3:{
        bonus.setTexture(m_bonus3Texture);
        bonus.setType(Bonus::PaddleSpeedUp); // Ustawianie typu bonusu na PrzyspieszeniePaletki
        break;
    }
    default: {
        std::cerr << "Unknown bonus type." << std::endl;
        return;
    }
    }
    bonus.setPosition(x, y);
    m_bonuses.push_back(bonus);
}


// tworzenie paletki
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

// tworzenie piłki
void Game::createBall() {
    if(m_shop.getSelectedTexture().getSize().x !=0 ||m_shop.getSelectedTexture().getSize().y!=0){
        m_ballSprite.setTexture(m_shop.getSelectedTexture());
    }
    else{
        m_ballSprite.setTexture(m_ballTexture);
    }
    m_ballSprite.setPosition(864, 600);
    float originalWidth = m_ballTexture.getSize().x;
    float originalHeight = m_ballTexture.getSize().y;

    float desiredWidth = 20.f;
    float desiredHeight = 20.f;

    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;

    m_ballSprite.setScale(scaleX, scaleY);
}
// tworzenie bloków
void Game::createBlocks() {

    // Tworzenie przykładowych bloków i wierszy i kolumn
    int rows = 6;
    int columns = 17; //17
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

// funkcja zapisująca coinsy do pliku
void Game::saveCoinsToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << coins;
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}

// funkcja wczytująca coinsy z pliku
void Game::loadCoinsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> coins;
        file.close();
    } else {
        std::cerr << "Error: Could not open file for reading." << std::endl;
    }
}
void Game::showMenu() {
    m_isInMenu = true;
}

void Game::startGame() {
    m_objects.clear();
    createPaddle();
    createBall();
    createBlocks();
    m_gameClock.restart();
    m_isMovingLeft = false;  // Zresetuj zmienne odpowiadające za ruch paletki
    m_isMovingRight = false;
    m_lives=3;
    m_isBallAttached = true;
}

void Game::showSettings() {
    m_menu.showSettings([this](int soundtrackVolume, int collisionVolume) {
        sm.setSoundtrackVolume(soundtrackVolume);
        sm.setCollisionVolume(collisionVolume);
    });
}

void Game::showShop() {
    m_isInShop = true;
}
