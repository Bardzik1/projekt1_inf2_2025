#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define MAX_LICZBA_POZIOMOW 4

class Menu
{
private:
    sf::Font font;
    std::vector<sf::Text> menu;
    int selectedItem = 0;

public:
    Menu(float width, float height);
    ~Menu() = default;
    void przesunG();
    void przesunD();
    int getSelectedItem() const { return selectedItem; }
    void draw(sf::RenderWindow& window);
};