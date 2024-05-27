#include "Game.h"

Game::Game() : mWindow(sf::VideoMode(800,600), "Super Galaxy Arkanoid")
{}

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
