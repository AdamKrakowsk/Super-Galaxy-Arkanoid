#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    // Deklaracja funkcji i zmiennych
    Menu(float width, float height);
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    void showSettings(std::function<void(int, int)> setVolumes);
    void showHighscore();
    int getPressedItem() const { return selectedItemIndex; }



private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    int highscore;
};

#endif // MENU_H
