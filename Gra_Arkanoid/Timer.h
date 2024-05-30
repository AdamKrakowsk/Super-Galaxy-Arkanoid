#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics.hpp>

class Timer {
public:
    Timer();
    void restart();
    void update();
    void draw(sf::RenderWindow& window);

private:
    sf::Clock m_clock;
    sf::Font m_font;
    sf::Text m_text;
};

#endif // TIMER_H
