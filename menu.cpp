#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    
    const char* fontPaths[] = {
        "fonts/arial.ttf",
        "../fonts/arial.ttf",
        "../../fonts/arial.ttf",
        "arial.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };

    bool fontLoaded = false;
    for (const char* path : fontPaths) {
        if (font.openFromFile(path)) {
            std::cout << "Sciezka zaladowanej czcionki: " << path << std::endl;
            fontLoaded = true;
            break;
        }
    }

    if (!fontLoaded) {
        std::cout << "Nie zaladowano czcionki" << std::endl;
        
    }

   
    menu.push_back(sf::Text(font, "Nowa gra"));
    menu.push_back(sf::Text(font, "Wczytaj gre"));
    menu.push_back(sf::Text(font, "Ostatnie wyniki"));
    menu.push_back(sf::Text(font, "Wyjscie"));

   
    menu[0].setFillColor(sf::Color::Cyan);
    menu[0].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1));
    menu[0].setStyle(sf::Text::Bold);

    menu[1].setFillColor(sf::Color::White);
    menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));

    menu[2].setFillColor(sf::Color::White);
    menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));

    menu[3].setFillColor(sf::Color::White);
    menu[3].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 4));

    selectedItem = 0;

    std::cout << "Menu created with " << menu.size() << " items" << std::endl;
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::przesunG()
{
    if (menu.empty()) return;

    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);

    selectedItem--;
    if (selectedItem < 0)
        selectedItem = MAX_LICZBA_POZIOMOW - 1;

    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void Menu::przesunD()
{
    if (menu.empty()) return;

    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);

    selectedItem++;
    if (selectedItem >= MAX_LICZBA_POZIOMOW)
        selectedItem = 0;

    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}