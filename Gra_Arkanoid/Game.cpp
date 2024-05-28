#include "Game.h"
#include "Object.h"

Game::Game() : mWindow(sf::VideoMode(800,600), "Super Galaxy Arkanoid")
{
    m_backgroundTexture.loadFromFile("background.png");

    // Ustawianie tła
    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(static_cast<float>(mWindow.getSize().x) / m_backgroundTexture.getSize().x,
                                static_cast<float>(mWindow.getSize().y) / m_backgroundTexture.getSize().y);
}

Game::~Game() {}

void Game::run() {
    sf::Clock clock;
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(5);
    triangle.setPosition(600.0, 100.0);
    while (mWindow.isOpen()) {

        mWindow.draw(triangle);
    }
}
