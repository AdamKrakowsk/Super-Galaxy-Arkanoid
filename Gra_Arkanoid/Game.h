#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>

class Object;

class Game
{
public:
    Game();
    ~Game();
    void run();

private:

     void render();


    sf::RenderWindow mWindow;
    std::vector<std::unique_ptr<Object>> m_objects;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    sf::Texture m_paddleTexture;
    sf::Sprite m_paddleSprite;


    void createPaddle();
    float m_PaddleSpeed;
    sf::Vector2f m_PaddleVelocity;


};

#endif // GAME_H
