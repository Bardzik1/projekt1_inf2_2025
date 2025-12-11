#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameOverScreen
{
private:
    sf::Font font;

    sf::Text titleText;
    sf::Text scoreText;
    sf::Text infoText;
    sf::RectangleShape background;

public:
    GameOverScreen(float width, float height);

    void setScore(int score);

    void draw(sf::RenderWindow& window);
};