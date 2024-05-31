#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "SoundManager.h"
#include "Highscore.h"
#include "Timer.h"
#include "Bonus.h"

class Object;

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void render();
    void processEvents();
    void update(sf::Time deltaTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void createPaddle();
    void createBall();
    void createBlocks();
    void createBonus(float x, float y, int bonustype);
    void restartGame();
    void saveCoinsToFile(const std::string& filename);
    void loadCoinsFromFile(const std::string& filename);


    sf::RenderWindow mWindow;
    std::vector<std::unique_ptr<Object>> m_objects;
    std::vector<std::pair<sf::Sprite, sf::Vector2f>> m_balls;
    std::vector<Bonus> m_bonuses;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    sf::Texture m_paddleTexture;
    sf::Sprite m_paddleSprite;
    sf::Texture m_ballTexture;
    sf::Sprite m_ballSprite;
    sf::Texture m_blockTexture;
    sf::Sprite m_blockSprite;
    sf::Texture m_clearTexture;
    sf::Texture m_bonusTexture;
    sf::Texture m_bonus1Texture;
    sf::Texture m_bonus2Texture;


    Paddle m_paddle;
    Ball m_ball;
    SoundManager sm;

    float m_PaddleSpeed;
    float m_BallSpeed;
    float lastH=50.f;
    float lastW=200.f;

    int bonuslos=0;

    sf::Vector2f m_PaddleVelocity;
    sf::Vector2f m_ballVelocity;

    bool m_isMovingLeft = false;
    bool m_isMovingRight = false;
    bool m_isBallAttached = true;

    Highscore m_highscore;
    Timer m_timer;
    sf::Clock m_gameClock; // Zegar do mierzenia czasu trwania gry
    bool m_gameOver;
    sf::Font m_font;  // Dodajemy czcionkę
    sf::Text m_currentTimeText;  // Tekst aktualnego czasu
    sf::Text m_highscoreText;  // Tekst highscore

    int coins;
    sf::Text m_coinsText;
};

#endif // GAME_H
