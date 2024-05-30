#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

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

    sf::RenderWindow mWindow;
    std::vector<std::unique_ptr<Object>> m_objects;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    sf::Texture m_paddleTexture;
    sf::Sprite m_paddleSprite;
    sf::Texture m_ballTexture;
    sf::Sprite m_ballSprite;
    sf::Texture m_blockTexture;
    sf::Sprite m_blockSprite;

    Paddle m_paddle;
    Ball m_ball;

    float m_PaddleSpeed;
    float m_BallSpeed;

    sf::Vector2f m_PaddleVelocity;
    sf::Vector2f m_ballVelocity;

    bool m_isMovingLeft = false;
    bool m_isMovingRight = false;
    bool m_isBallAttached = true;
};

#endif // GAME_H
